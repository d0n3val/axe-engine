/**
* @file
* Axe 'system_info' library PUBLIC include header
* @author	Ricard Pillosu <doneval\@users.sf.net>
* @version	0.1
* @date		25/11/2003
*/
#ifndef __AXE_SYSTEM_INFO_H__
  #define __AXE_SYSTEM_INFO_H__

  #include <time.h>

// ------------------------------------------
/// Lib version
  #define AXE_SYSTEM_INFO_VERSION 1
  #define AXE_SYSTEM_INFO_NAME    "SYSTEM_INFO"
  #define AXE_SYSTEM_INFO_LIBID   'AXSI'

// ------------------------------------------
/// DLL proper function prefix
  #ifdef AXE_SYSTEM_INFO_DLL
    #define AXSI_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'system_info' library ..." )
  #else
    #define AXSI_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'system_info' library ..." )

// ------------------------------------------
	/// Automatic .lib link ... define AXSI_NO_AUTOLINK
	/// if you want to make your own .lib link
    #ifndef AXSI_NO_AUTOLINK
      #ifdef _DEBUG
        #pragma comment( lib, "axe_system_info_debug.lib" )
      #else
        #pragma comment( lib, "axe_system_info.lib" )
      #endif
    #endif
  #endif

/*$1-  Axe Id ----------------------------------------------------------------*/
  #ifndef AXE_ID
    #define AXE_ID  unsigned int
  #endif

// ------------------------------------------
/// Axe boolean values
  #ifndef AXE_TRUE
    #define AXE_TRUE  1
  #endif
  #ifndef AXE_FALSE
    #define AXE_FALSE 0
  #endif

// ------------------------------------------
/// States for this lib
enum axsi_states
{
  AXSI_VERSION      = 1,
  AXSI_LIBRARY_NAME,
  AXSI_LIBRARY_ID,
  AXSI_MODE,
  AXSI_LAST_ERROR,
  AXSI_ERROR_OUTPUT,
  AXSI_DUMP_OUTPUT,
  AXSI_STATE_COUNT,
};

/*$1- Standard Outputs for errors and dumps ----------------------------------*/
enum axsi_outputs
{
  AXSI_NONE         = 1,
  AXSI_OUTPUT_DEBUG,
  AXSI_MESSAGE_BOX,
  AXSI_DBG_MSG_BOX,
  AXSI_FILE,
  AXSI_BREAKPOINT,
};

/*$1- Values for mode state --------------------------------------------------*/
enum axsi_modes
{
  AXSI_DEBUG        = 1,
  AXSI_RELEASE
};

enum axsi_platforms
{
  AXSI_WINDOWS_UNKNOWN= 1,
  AXSI_WINDOWS_OLD,
  AXSI_WINDOWS_95,
  AXSI_WINDOWS_95_SR2,
  AXSI_WINDOWS_98,
  AXSI_WINDOWS_98_SE,
  AXSI_WINDOWS_ME,
  AXSI_WINDOWS_NT3,
  AXSI_WINDOWS_NT4,
  AXSI_WINDOWS_2K,
  AXSI_WINDOWS_XP,
  AXSI_WINDOWS_2003,
  AXSI_WINDOW_FUTURE
};

enum axsi_dx_versions
{
  AXSI_DX_NO_INSTALLED= 1,
  AXSI_DX_UNKNOWN,
  AXSI_DX_1,
  AXSI_DX_2,
  AXSI_DX_3,
  AXSI_DX_3a,
  AXSI_DX_5,
  AXSI_DX_6,
  AXSI_DX_61,
  AXSI_DX_61a,
  AXSI_DX_7,
  AXSI_DX_7a,
  AXSI_DX_8,
  AXSI_DX_81,
  AXSI_DX_81a,
  AXSI_DX_81b,
  AXSI_DX_82,
  AXSI_DX_9,
  AXSI_DX_9a,
  AXSI_DX_9b,
  AXSI_DX_FUTURE
};

enum axsi_cpu_vendor
{
  AXSI_CPU_VENDOR_UNKNOWN = 1,
  AXSI_CPU_VENDOR_CENTAUR,
  AXSI_CPU_VENDOR_CYRIX,
  AXSI_CPU_VENDOR_AMD,
  AXSI_CPU_VENDOR_INTEL
};

enum axsi_cpu_type
{
  AXSI_CPU_OLD            = 1,
  AXSI_CPU_PENTIUM1,
  AXSI_CPU_PENTIUM2,
  AXSI_CPU_PENTIUM3,
  AXSI_CPU_PENTIUM4,
  AXSI_CPU_FUTURE
};

enum axsi_display_vendor
{
  AXSI_GPU_VENDOR_UNKNOWN = 1,
  AXSI_GPU_VENDOR_ATI,
  AXSI_GPU_VENDOR_NVIDIA
};

enum axsi_display_type
{
  AXSI_GPU_UNKNOWN        = 1,
  AXSI_NO_3D_ACCEL,
  AXSI_3D_ACCEL,
  AXSI_SHADERS
};

  #define AXSI_INFO_STRLEN  250

struct axsi_system
{
  // platform ---------------------------------
  int           platform;
  int           directx_version;

  // cpu --------------------------------------
  int           cpu_count;
  int           cpu_family;
  int           cpu_model;
  int           cpu_stepping;
  int           cpu_vendor;
  int           cpu_type;
  unsigned int  cpu_speed;
  char          cpu_name[AXSI_INFO_STRLEN];

  // mem --------------------------------------
  unsigned int  total_ram;
  unsigned int  total_real_ram;
  unsigned int  free_ram;
  unsigned int  free_real_ram;

  // hd ---------------------------------------
  unsigned int  total_hd;
  unsigned int  free_hd;

  // dirs -------------------------------------
  char          windows_dir[AXSI_INFO_STRLEN];
  char          system_dir[AXSI_INFO_STRLEN];

  // misc -------------------------------------
  char          machine_name[AXSI_INFO_STRLEN];
  char          user_name[AXSI_INFO_STRLEN];
};

struct axsi_cpu_flags
{
  int fpu;
  int cpuid;
  int rdtsc;
  int apic;
  int cmov;
  int mtrr;
  int mmx;
  int sse;
  int sse2;
  int f3dnow;
  int f3dnow_ex;
  int fastcall;
  int htt;
  int fxsr;
};

struct axsi_display
{
  // device -----------------------------------
  int           device_enabled;
  char          device_name[AXSI_INFO_STRLEN];
  char          device_chip_name[AXSI_INFO_STRLEN];
  char          device_dac_name[AXSI_INFO_STRLEN];
  int           device_vendor;
  unsigned int  device_total_ram;
  time_t        device_driver_date;
  char          device_driver_version[AXSI_INFO_STRLEN];
  int           device_hardware_accel_enabled;

  // monitor ----------------------------------
  int           monitor_maxres_width;
  int           monitor_maxres_height;
  int           monitor_res_width;
  int           monitor_res_height;
  int           monitor_res_bpp;
  int           monitor_refresh_rate;

  // misc -------------------------------------
  int           agp_enabled;
};

struct axsi_input
{
  // device -----------------------------------
  int mouse_enabled;
  int keyboard_enabled;
  int joystick_enabled;
};

struct axsi_sound
{
  // device -----------------------------------
  int   device_enabled;
  char  device_name[AXSI_INFO_STRLEN];
  int   device_acceleration_level;

  // music ----------------------------------
  int   music_enabled;
  int   music_accel;
};

struct axsi_network
{
  // device -----------------------------------
  int device_enabled;
};

/** @example axsi_test.cpp */
// Our interface is entirely coded in C --------------------------------------
extern "C"
{
  // axsi_system_info.cpp ------------------------------------------------------
  #define axsi_get( query_state )             axsi_get_int( query_state )
  #define axsi_set( query_state, new_value )  axsi_set_int( query_state, new_value )
  #define axsi_get_error()                    axsi_get_error_number()
  AXSI_API int          axsi_get_int( const int query_state );
  AXSI_API int          axsi_set_int( const int query_state, const int new_value );
  AXSI_API const char*  axsi_get_error_message( const int error_number );

  // axsi_system.cpp -----------------------------------------------------------
  AXSI_API int          axsi_get_system( axsi_system* system_info );

  // axsi_cpu_flags.cpp -----------------------------------------------------------
  AXSI_API int          axsi_get_cpu_flags( axsi_cpu_flags* cpu_flags_info );

  // axsi_display.cpp -----------------------------------------------------------
  AXSI_API int          axsi_get_display( axsi_display* display_info );

  // axsi_input.cpp -----------------------------------------------------------
  AXSI_API int          axsi_get_input( axsi_input* input_info );

  // axsi_sound.cpp -----------------------------------------------------------
  AXSI_API int          axsi_get_sound( axsi_sound* sound_info );

  // axsi_network.cpp -----------------------------------------------------------
  AXSI_API int          axsi_get_network( axsi_network* network_info );

  // axsi_ram.cpp --------------------------------------------------------------
  AXSI_API unsigned int axsi_get_total_ram();
  AXSI_API unsigned int axsi_get_total_real_ram();
  AXSI_API unsigned int axsi_get_free_ram();
  AXSI_API unsigned int axsi_get_free_real_ram();
  AXSI_API int          axsi_get_percent_used_ram();

  // axsi_cpu_flags.cpp --------------------------------------------------------
  AXSI_API int          axsi_cpu_check_fpu();
  AXSI_API int          axsi_cpu_check_cpuid();
  AXSI_API int          axsi_cpu_check_rdtsc();
  AXSI_API int          axsi_cpu_check_apic();
  AXSI_API int          axsi_cpu_check_cmov();
  AXSI_API int          axsi_cpu_check_mtrr();
  AXSI_API int          axsi_cpu_check_mmx();
  AXSI_API int          axsi_cpu_check_3dnow();
  AXSI_API int          axsi_cpu_check_3dnow_ex();
  AXSI_API int          axsi_cpu_check_simd();
  AXSI_API int          axsi_cpu_check_simd2();
  AXSI_API int          axsi_cpu_check_fastcall();
  AXSI_API int          axsi_cpu_check_htt();
  AXSI_API int          axsi_cpu_check_fxsr();

  // axsi_platform.cpp ---------------------------------------------------------
  AXSI_API int          axsi_os_version();
  AXSI_API const char*  axsi_os_version_string();
  AXSI_API int          axsi_directx_version();
  AXSI_API const char*  axsi_directx_version_string();

  /*
gpu_buffer_mem ?
AGP mem ?
// there is CD ?

ScreenSaver -> SystemParametersInfo()

*/
} // extern "C"
#endif // __AXE_SYSTEM_INFO_H__

/* $Id: axe_system_info.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
