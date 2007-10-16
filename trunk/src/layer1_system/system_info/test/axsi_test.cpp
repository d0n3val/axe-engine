/**
* @file
* Axe 'system_info' test code
* @see axe_system_info.h
*/
#include "axsi_test.h"

#define AXSI_NO_AUTOLINK
#include "../src/axe_system_info.h"

/// Version of this test code
#define AXE_SYSTEM_INFO_TEST_VERSION  1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../output_debug/lib/system_info.lib" )
#else
  #pragma comment( lib, "../output_release/lib/system_info.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
int check_error() {
  int error = axsi_get( AXSI_LAST_ERROR );

  if( error != 0 ) {
    printf( "Error: %s\n", axsi_get_error_message(error) );
    getchar();
    return( 0 );
  }

  printf( "OK\n" );
  return( 1 );
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axsi_get( AXSI_VERSION );

  if( !check_error() ) {
    return( 0 );
  }

  if( lib_version != AXE_SYSTEM_INFO_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_SYSTEM_INFO_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_SYSTEM_INFO_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'system_info' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  axsi_system     system;
  axsi_cpu_flags  cpu_flags;
  axsi_display    display;
  axsi_sound      sound;

  // SYSTEM ---------------------------------------------
  printf( "Gathering System info ..." );
  axsi_get_system( &system );
  check_error();

  printf( "OS:\t\t%s (%d)\n", axsi_os_version_string(), system.platform );
  printf( "DirectX:\t%s (%d)\n\n", axsi_directx_version_string(), system.directx_version );

  printf( "RAM:\t\t%u used %u total MB\n", system.free_ram / 1024, system.total_ram / 1024 );
  printf( "Real RAM:\t%u used %u total MB\n\n", system.free_real_ram / 1024, system.total_real_ram / 1024 );

  printf( "CPU count:\t%d\n", system.cpu_count );
  printf( "CPU info:\tfamily %d model %d stepping %d\n", system.cpu_family, system.cpu_model, system.cpu_stepping );
  printf( "CPU vendor:\t%d\n", system.cpu_vendor );
  printf( "CPU type:\t%d\n", system.cpu_type );
  printf( "CPU name:\t%s\n", system.cpu_name );
  printf( "CPU speed:\t%u Mhz\n", system.cpu_speed );

  // CPU FLAGS ---------------------------------------------
  printf( "---\nNow gathering cpu capabilities ..." );
  axsi_get_cpu_flags( &cpu_flags );
  check_error();

  printf( "FPU:\t%d\n", cpu_flags.fpu );
  printf( "CPUID:\t%d\n", cpu_flags.cpuid );
  printf( "RDTSC:\t%d\n", cpu_flags.rdtsc );
  printf( "MMX:\t%d\n", cpu_flags.mmx );
  printf( "3DNOW:\t%d\n", cpu_flags.f3dnow );
  printf( "3DNOW2:\t%d\n", cpu_flags.f3dnow_ex );
  printf( "SSE:\t%d\n", cpu_flags.sse );
  printf( "SSE2:\t%d\n", cpu_flags.sse2 );
  printf( "APIC:\t%d\n", cpu_flags.apic );
  printf( "CMOV:\t%d\n", cpu_flags.cmov );
  printf( "MTRR:\t%d\n", cpu_flags.mtrr );
  printf( "SEP:\t%d\n", cpu_flags.fastcall );
  printf( "HTT:\t%d\n", cpu_flags.htt );
  printf( "FXSR:\t%d\n", cpu_flags.fxsr );

  // DISPLAY ----------------------------------------------
  printf( "---\nNow gathering display capabilities ..." );
  axsi_get_display( &display );
  check_error();

  if( display.device_enabled == AXE_TRUE ) {
    printf( "Device name:\t%s\n", display.device_name );
    printf( "Chip name:\t%s\n", display.device_chip_name );
    printf( "DAC:\t\t%s\n", display.device_dac_name );
    printf( "Vendor ID:\t%d (nvidia=3, ati=2, other=1)\n", display.device_vendor );
    printf( "Device RAM:\t%u\n", display.device_total_ram );

    printf( "Driver date:\t%s\n", ctime(&display.device_driver_date) );
    printf( "Driver version:\t%s\n", display.device_driver_version );
    printf( "Hardware accel:\t%d\n", display.device_hardware_accel_enabled );
    printf( "AGP Enabled:\t%d\n", display.agp_enabled );

    printf( "Monitor Max:\t%d x %d\n", display.monitor_maxres_width, display.monitor_maxres_height );
    printf( "Monitor Res:\t%d x %d\n", display.monitor_res_width, display.monitor_res_height );
    printf( "Monitor BPP:\t%d\n", display.monitor_res_bpp );
    printf( "Monitor Hz:\t%d\n", display.monitor_refresh_rate );
  } else {
    printf( "No suitable display device found\n" );
  }

  // SOUND ----------------------------------------------
  printf( "---\nNow gathering sound capabilities ..." );
  axsi_get_sound( &sound );
  check_error();

  if( sound.device_enabled == AXE_TRUE ) {
    printf( "Device name:\t%s\n", sound.device_name );
    printf( "Device accel:\t%d\n", sound.device_acceleration_level );

    if( sound.music_enabled == AXE_TRUE ) {
      printf( "Music accel:\t%d\n", sound.music_accel );
    } else {
      printf( "No suitable music device found\n" );
    }
  } else {
    printf( "No suitable sound device found\n" );
  }

  // Finish --------------------------------------------
  printf( "\nAxe 'system_info' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axsi_test.cpp,v 1.1 2004/06/09 18:23:58 doneval Exp $ */
