/**
* @file
* Axe 'system_info' code for gathering system information
*/
#include "axsi_stdafx.h"

#define AXSI_DIV_MEM  1024

extern _state state;

/// Global state of the library

/**
* Comment
*/
int axsi_get_system( axsi_system* system_info ) {
  if( system_info == NULL ) {
    axsi_set_error( 3 );
    return( AXE_FALSE );
  }

  MEMORYSTATUS  mem_stats;

  GlobalMemoryStatus( &mem_stats );

  if( state.system_set == false ) {

    // platform ---------------------------------
    state.system_data.platform = axsi_os_version();
    state.system_data.directx_version = axsi_directx_version();

    // cpu --------------------------------------
    state.system_data.cpu_count = get_cpu_count();
    state.system_data.cpu_family = get_cpu_family();
    state.system_data.cpu_model = get_cpu_model();
    state.system_data.cpu_stepping = get_cpu_stepping();
    state.system_data.cpu_vendor = get_cpu_vendor();
    state.system_data.cpu_type = get_cpu_type_id(
        state.system_data.cpu_family,
        state.system_data.cpu_model,
        state.system_data.cpu_vendor );
    state.system_data.cpu_speed = get_cpu_speed();
    strcpy(
      state.system_data.cpu_name,
      get_cpu_name(state.system_data.cpu_family, state.system_data.cpu_model, state.system_data.cpu_vendor) );

    // mem --------------------------------------
    state.system_data.total_ram = (unsigned int) ( mem_stats.dwTotalPhys + mem_stats.dwTotalPageFile ) / AXSI_DIV_MEM;
    state.system_data.total_real_ram = (unsigned int) ( mem_stats.dwTotalPhys / AXSI_DIV_MEM );

    // hd ---------------------------------------
    state.system_data.total_hd = 0;         /// @todo

    // dirs -------------------------------------
    TCHAR tmp[AXSI_INFO_STRLEN];

    GetWindowsDirectory( &tmp[0], AXSI_INFO_STRLEN );
    strncpy( state.system_data.windows_dir, tmp, AXSI_INFO_STRLEN );
    state.system_data.windows_dir[AXSI_INFO_STRLEN - 1] = 0;

    GetSystemDirectory( &tmp[0], AXSI_INFO_STRLEN );
    strncpy( state.system_data.system_dir, tmp, AXSI_INFO_STRLEN );
    state.system_data.system_dir[AXSI_INFO_STRLEN - 1] = 0;

    // misc -------------------------------------
    DWORD size_buf = AXSI_INFO_STRLEN;

    GetComputerName( &tmp[0], &size_buf );
    strncpy( state.system_data.machine_name, tmp, AXSI_INFO_STRLEN );
    state.system_data.machine_name[AXSI_INFO_STRLEN - 1] = 0;

    size_buf = AXSI_INFO_STRLEN;
    GetUserName( &tmp[0], &size_buf );
    strncpy( state.system_data.user_name, tmp, AXSI_INFO_STRLEN );
    state.system_data.user_name[AXSI_INFO_STRLEN - 1] = 0;
  }

  // Refresh real-time data
  state.system_data.free_ram = (unsigned int) ( mem_stats.dwAvailPhys + mem_stats.dwAvailPageFile ) / AXSI_DIV_MEM;
  state.system_data.free_real_ram = (unsigned int) ( mem_stats.dwAvailPhys / AXSI_DIV_MEM );

  state.system_data.free_hd = 0;            /// @todo
  memcpy( system_info, &state.system_data, sizeof(axsi_system) );

  state.system_set = true;

  return( AXE_TRUE );
}

/**
* Comment
*/
int get_cpu_count() {
  SYSTEM_INFO sys_info;
  GetSystemInfo( &sys_info );
  return( (int) sys_info.dwNumberOfProcessors );
}

/**
* Comment
*/
unsigned int get_cpu_speed() {

  // We need RDTSC
  if( cpu_check_rdtsc() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  unsigned int  start;

  unsigned int  end;

  unsigned int  elapsed;
  axsi_timer    timer;

  timer.start();                            // start the timer
  start = read_cpu_counter();               // sample the cpu counter
  Sleep( 100 );                             // waste some time
  end = read_cpu_counter();                 // resample the cpu counter
  timer.stop();                             // stop the clock
  elapsed = (unsigned int) timer.elapsed(); // calc elapsed time
  if( elapsed < 1 ) {

    // make sure time is non-zero
    return( AXE_FALSE );
  }

  // compute the CPU speed as ticks per millisecond
  return( (unsigned int) ((end - start) / elapsed) / 1000 );
}

/**
* Comment
*/
int get_cpu_family() {

  // get cpu flags
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  return( (state.cpu_info >> 8) & 0xF );
}

/**
* Comment
*/
int get_cpu_model() {

  // get cpu flags
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  return( (state.cpu_info >> 4) & 0xF );
}

/**
* Comment
*/
int get_cpu_stepping() {

  // get cpu flags
  if( read_cpu_flags() == AXE_FALSE ) {
    return( AXE_FALSE );
  }

  return( (state.cpu_info) & 0xF );
}

/**
* Comment
*/
int get_cpu_vendor() {

  // we need CPUID
  if( cpu_check_cpuid() == AXE_FALSE ) {
    return( NULL );
  }

  // go on
  union
  {
    char  str[12 + 1];
    struct
    {
      unsigned long ul0;
      unsigned long ul1;
      unsigned long ul2;
    } s;
  } vendor;

  _asm
  {
    push ebx
    push ecx
    push edx

    // get the vendor string
    xor eax, eax
    cpuid
    mov vendor.s.ul0, ebx
    mov vendor.s.ul1, edx
    mov vendor.s.ul2, ecx

    pop edx
    pop ecx
    pop ebx
  };

  vendor.str[12] = 0;

  if( !strncmp("GenuineIntel", vendor.str, 12) ) {
    return( AXSI_CPU_VENDOR_INTEL );
  }

  if( !strncmp("AuthenticAMD", vendor.str, 12) ) {
    return( AXSI_CPU_VENDOR_AMD );
  }

  if( !strncmp("CyrixInstead", vendor.str, 12) ) {
    return( AXSI_CPU_VENDOR_CYRIX );
  }

  if( !strncmp("CentaurHauls", vendor.str, 12) ) {
    return( AXSI_CPU_VENDOR_CENTAUR );
  }

  return( AXSI_CPU_VENDOR_UNKNOWN );
}

/**
* Comment
*/
int get_cpu_type_id( const int family, const int model, const int vendor ) {
  int             tech;
  axsi_cpu_flags  cpu_flags;

  tech = AXSI_CPU_OLD;
  axsi_get_cpu_flags( &cpu_flags );

  // check directly for cpu flags to know what ty0pe of cpu we have
  if( cpu_flags.cpuid == AXE_TRUE && cpu_flags.fpu == AXE_TRUE ) {
    tech = AXSI_CPU_PENTIUM1;
  }

  if( tech == AXSI_CPU_PENTIUM1 && cpu_flags.cmov == AXE_TRUE && cpu_flags.mmx == AXE_TRUE ) {
    tech = AXSI_CPU_PENTIUM2;
  }

  if( tech == AXSI_CPU_PENTIUM2 && (cpu_flags.sse == AXE_TRUE || cpu_flags.f3dnow == AXE_TRUE) ) {
    tech = AXSI_CPU_PENTIUM3;
  }

  if( tech == AXSI_CPU_PENTIUM3 && (cpu_flags.sse2 == AXE_TRUE || cpu_flags.f3dnow_ex == AXE_TRUE) ) {
    tech = AXSI_CPU_PENTIUM4;
  }

  return( tech );
}

/**
* Comment
*/
const char* get_cpu_name( const int family, const int model, const int vendor ) {
  switch( vendor )
  {
    // AMD -----------------------------------------------------------------------------
    case AXSI_CPU_VENDOR_AMD:
      switch( family )
      {
        case 4:                             // Am486/AM5x86
          return( "AMD Am486" );

        case 5:                             // K6
          switch( model )
          {                                 // extract model code
            case 0:
            case 1:
            case 2:
            case 3:
              return( "AMD K5" );

            case 6:
            case 7:
              return( "AMD K6" );

            case 8:
              return( "AMD K6-2" );

            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
              return( "AMD K6-3" );
          }

          break;

        case 6:                             // Athlon
          return( "AMD Athlon" );
          break;
      }

    // INTEL -----------------------------------------------------------------------------
    case AXSI_CPU_VENDOR_INTEL:
      switch( family )
      {
        case 4:
          switch( model )
          {
            case 0:
            case 1:
              return( "INTEL 486DX" );

            case 2:
              return( "INTEL 486SX" );

            case 3:
              return( "INTEL 486DX2" );

            case 4:
              return( "INTEL 486SL" );

            case 5:
              return( "INTEL 486SX2" );

            case 7:
              return( "INTEL 486DX2E" );

            case 8:
              return( "INTEL 486DX4" );
          }

          break;

        case 5:
          switch( model )
          {
            case 1:
            case 2:
            case 3:
              return( "INTEL Pentium" );

            case 4:
              return( "INTEL Pentium-MMX" );

            case 8:
              return( "INTEL Mobile Pentium" );
          }

          break;

        case 6:
          switch( model )
          {
            case 1:
              return( "INTEL Pentium-Pro" );

            case 3:
            case 5:
              // actual differentiation depends on cache settings
              return( "INTEL Pentium-II" );

            case 6:
              return( "INTEL Celeron" );

            case 7:
            case 8:
            case 10:
            case 11:
              // actual differentiation depends on cache settings
              return( "INTEL Pentium-III" );
          }

          break;

        //case 15 | (0x00 << 4): // family 15, extended family 0x00
        case 15:
          return( "INTEL Pentium-4" );
      }

    // OTHERS -----------------------------------------------------------------------------
    case AXSI_CPU_VENDOR_CYRIX:
      return( "Cyrix" );

    case AXSI_CPU_VENDOR_CENTAUR:
      return( "Centaur" );

    // ?? ---------------------------------------------------------------------------------
    default:
      return( "Unknown" );
  }

  return( NULL );
}

/**
* Comment
*/
unsigned int read_cpu_counter() {

  // check cached data
  if( cpu_check_rdtsc() == AXE_FALSE ) {

    // here we return 100 just in case main code
    // want to divide it
    return( 100 );
  }

  unsigned int    counter;

  unsigned int*   p_counter;
  p_counter = &counter;

  _asm
  {
    RDTSC
    mov edi, p_counter
    mov DWORD PTR[edi], eax

    //mov DWORD PTR [edi+4], edx	// in case we want more precision
  };

  return( counter );
}

/* $Id: axsi_system.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
