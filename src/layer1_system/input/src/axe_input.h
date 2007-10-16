/**
* @file
* Axe 'input' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  18 May 2004
*/
#ifndef __AXE_INPUT_H__
  #define __AXE_INPUT_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXIP_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Input' ..." )
  #else
    #define AXIP_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Input' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXIP_NO_AUTOLINK
      #pragma comment( lib, "axe_input.lib" )
    #endif
  #endif

/*$1- Max lenght for a device name -------------------------------------------*/
  #define AXIP_MAX_DEVICE_NAME_LEN  MAX_PATH

/*$1- States for this lib ----------------------------------------------------*/
enum axip_states
{
  AXIP_VERSION      = 1,
  AXIP_LIBRARY_NAME,
  AXIP_LIBRARY_ID,
  AXIP_DEBUG_MODE,
  AXIP_LAST_ERROR,
  AXIP_STATE_COUNT,
};

/** @example axip_test.cpp */
extern "C"
{
  /**
  * List of device types
  */
  enum axip_device_type
  {
    AXIP_DEVICE_UNKNOWN = 0,
    AXIP_DEVICE_KEYBOARD,
    AXIP_DEVICE_MOUSE,
    AXIP_DEVICE_JOYSTICK
  };

  /**
  * List of all possible type of events
  */
  enum axip_event_type
  {
    AXIP_EVENT_NULL         = 0,
    AXIP_EVENT_KEY_PRESSED,
    AXIP_EVENT_KEY_RELEASED,
    AXIP_EVENT_AXIS_X,
    AXIP_EVENT_AXIS_Y,
    AXIP_EVENT_AXIS_Z
  };

  /**
  * Public info for each device
  */
  struct axip_device_info
  {
    char              name[AXIP_MAX_DEVICE_NAME_LEN];
    axip_device_type  type;
    int               num_vkeys;
    int               active;
  };

  /**
  * Single event
  */
  struct axip_event
  {
    int             device;
    axip_event_type type;
    unsigned long   value;
    unsigned long   time;
  };

  /*$1- axip_input.cpp -------------------------------------------------------*/
  AXIP_API unsigned int axip_get( const int query_state );
  AXIP_API unsigned int axip_set( const int query_state, const unsigned int new_value );
  AXIP_API const char*  axip_get_error_message( const unsigned int error_number );
  AXIP_API int          axip_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axip_init.cpp --------------------------------------------------------*/
  AXIP_API int  axip_init( HWND window, HINSTANCE instance );
  AXIP_API int  axip_done();

  /*$1- axip_get_info.cpp ----------------------------------------------------*/
  AXIP_API int          axip_get_num_devices();
  AXIP_API int          axip_get_device( const int num_device, axip_device_info* device_info );
  AXIP_API const char*  axip_get_device_name( const int num_device );

  /*$1- axip_events.cpp ------------------------------------------------------*/
  AXIP_API void               axip_set_active( const int num_device, int active );
  AXIP_API const axip_event*  axip_get_events();
  AXIP_API unsigned int       axip_get_num_events();
} // extern "C"
#endif // __AXE_INPUT_H__

/* $Id: axe_input.h,v 1.2 2004/07/21 22:08:51 doneval Exp $ */
