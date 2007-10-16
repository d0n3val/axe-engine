/**
* @file
* Axe 'control' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  19 Dec 2004
*/
#ifndef __AXE_CONTROL_H__
  #define __AXE_CONTROL_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXCO_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Control' ..." )
  #else
    #define AXCO_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Control' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXCO_NO_AUTOLINK
      #pragma comment( lib, "axe_control.lib" )
    #endif
  #endif

/*$1- Possible key states ----------------------------------------------------*/
enum axco_key_state
{
  AXCO_KEY_NONE   = 0,
  AXCO_KEY_PRESS  = 1,
  AXCO_KEY_REPEAT = 2,
  AXCO_KEY_RELEASE= 4
};

/*$1- Possible device types --------------------------------------------------*/
enum axco_device_type
{
  AXCO_DEV_NONE     = 0,
  AXCO_DEV_KEYBOARD,
  AXCO_DEV_MOUSE,
  AXCO_DEV_JOY
};

/*$1- States for this lib ----------------------------------------------------*/
enum axco_states
{
  AXCO_VERSION      = 1,
  AXCO_LIBRARY_NAME,
  AXCO_LIBRARY_ID,
  AXCO_DEBUG_MODE,
  AXCO_LAST_ERROR,
  AXCO_STATE_COUNT,
};

/*$1- Data struct of alerts fired --------------------------------------------*/
struct axco_alert_fired
{
  int alert_id;
};

/*$1- Return mouse position, absolute and relative ---------------------------*/
struct axco_mouse_info
{
  int   device_num;
  int   x, y;
  float relative_x, relative_y;
  int   min_x, min_y;
  int   max_x, max_y;
  float sensibility;
  int   precision;
  int   last_x_motion;
  int   last_y_motion;
};

/** @example axco_test.cpp */
extern "C"
{

  /*$1- axco_control.cpp -----------------------------------------------------*/
  AXCO_API unsigned int axco_get( const int query_state );
  AXCO_API unsigned int axco_set( const int query_state, const unsigned int new_value );
  AXCO_API const char*  axco_get_error_message( const unsigned int error_number );
  AXCO_API int          axco_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axco_init_configure.cpp ----------------------------------------------*/
  AXCO_API int              axco_init( HWND window, HINSTANCE instance );
  AXCO_API int              axco_done();
  AXCO_API int              axco_get_device_count();
  AXCO_API const char*      axco_get_device_name( int device_num );
  AXCO_API axco_device_type axco_get_device_type( int device_num );
  AXCO_API int              axco_is_device_active( int device_num );
  AXCO_API int              axco_set_device_active( int device_num, int active );
  AXCO_API int              axco_set_device_key_repeat_latency( int device_num, float latency_secs );

  /*$1- axco_update.cpp ------------------------------------------------------*/
  AXCO_API int  axco_set_update_rate( const float update_rate_in_seconds );
  AXCO_API int  axco_update();
  AXCO_API int  axco_is_key_pressed( int device_num, int key );

  /*$1- axco_alerts.cpp ------------------------------------------------------*/
  AXCO_API int  axco_begin_alert( int alert_id, float min_elapsed_secs = 0.0f );
  AXCO_API int  axco_add_event( int   device_num,
                                int   key,
                                int   state,
                                float elapsed_start = 0.0f,
                                float elapsed_end = 0.0f );
  AXCO_API int  axco_clear_events();
  AXCO_API int  axco_end_alert();

  /*$1- axco_alerts_fired.cpp ------------------------------------------------*/
  AXCO_API unsigned int             axco_get_num_alerts_fired();
  AXCO_API const axco_alert_fired*  axco_get_alerts_fired( unsigned int num = 0 );

  /*$1- axco_mouse.cpp -------------------------------------------------------*/
  AXCO_API int              axco_set_mouse_limits( int left, int top, int right, int bottom, int device_num = -1 );
  AXCO_API int              axco_set_mouse_pos( int x, int y, int device_num = -1 );
  AXCO_API int              axco_set_mouse_relative_pos( float x, float y, int device_num = -1 );
  AXCO_API axco_mouse_info  axco_get_mouse_info( int device_num = -1 );
  AXCO_API int              axco_set_mouse_sensibility( float sensibility, int device_num = -1 );
  AXCO_API int              axco_set_mouse_precision( int precision, int device_num = -1 );
  AXCO_API int              axco_get_mouse_motion( int device_num, int *x, int*y);
} // extern "C"
#endif // __AXE_CONTROL_H__

/* $Id: axe_control.h,v 1.5 2004/09/20 21:28:11 doneval Exp $ */
