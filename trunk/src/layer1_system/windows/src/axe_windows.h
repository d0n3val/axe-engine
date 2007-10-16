/**
* @file
* Axe 'windows' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  21 Dec 2003 
*/
#ifndef __AXE_WINDOWS_H__
  #define __AXE_WINDOWS_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXWD_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'windows' ..." )
  #else
    #define AXWD_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'windows' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXWD_NO_AUTOLINK
      #pragma comment( lib, "axe_windows.lib" )
    #endif
  #endif

/*$1-States for this lib -----------------------------------------------------*/
enum axwd_states
{
  AXWD_VERSION      = 1,
  AXWD_LIBRARY_NAME,
  AXWD_LIBRARY_ID,
  AXWD_DEBUG_MODE,
  AXWD_LAST_ERROR,
  AXWD_FULLSCREEN,
  AXWD_MAXIMIZED,
  AXWD_MINIMIZED,
  AXWD_PAUSED,
  AXWD_ENDING,
  AXWD_STARTED,
  AXWD_STATE_COUNT
};

/*$1- Standard Outputs for errors and dumps ----------------------------------*/
enum axwd_outputs
{
  AXWD_NONE         = 1,
  AXWD_OUTPUT_DEBUG,
  AXWD_MESSAGE_BOX,
  AXWD_DBG_MSG_BOX,
  AXWD_FILE,
  AXWD_BREAKPOINT,
};

/*$1- Window info ------------------------------------------------------------*/
struct win_info
{
  HINSTANCE instance;
  HWND      window;
  HDC       device_context;
  DWORD     window_style;
};

/*$1- Screen info ------------------------------------------------------------*/
struct screen_info
{
  int   screen_width, screen_height;
  int   window_width, window_height;
  int   left, top, right, bottom;
  float aspect_ratio;
};

/** @example axwd_test.cpp */
extern "C"
{

  /*$1- axlg_log.cpp ---------------------------------------------------------*/
  AXWD_API unsigned int axwd_get( const int query_state );
  AXWD_API unsigned int axwd_set( const int query_state, const unsigned int new_value );
  AXWD_API const char*  axwd_get_error_message( const unsigned int error_number );
  AXWD_API int          axwd_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axwd_application.cpp -------------------------------------------------*/
  AXWD_API int  axwd_start_application( HINSTANCE instance );
  AXWD_API int  axwd_reset_application();
  AXWD_API int  axwd_pause_application();
  AXWD_API int  axwd_resume_application();
  AXWD_API int  axwd_end_application();

  /*$1- axwd_callback.cpp ----------------------------------------------------*/
  AXWD_API int  axwd_on_main_loop( int (*func) () );
  AXWD_API int  axwd_on_start( int (*func) () );
  AXWD_API int  axwd_on_end( int (*func) () );
  AXWD_API int  axwd_on_resize( int (*func) (int, int, int, int, int) );
  AXWD_API int  axwd_on_focus( int (*func) (int) );

  /*$1- axwd_utils.cpp -------------------------------------------------------*/
  AXWD_API int          axwd_change_to_fullscreen();
  AXWD_API int          axwd_change_to_windowed();
  AXWD_API int          axwd_toggle_fullscreen();

  AXWD_API win_info     axwd_get_windows_info();
  AXWD_API screen_info  axwd_get_screen_info();

  AXWD_API int          axwd_show_cursor( int show_cursor );
  AXWD_API int          axwd_set_cursor( const char* cursor_file );
  AXWD_API int          axwd_set_icon( const char* icon_file );
  AXWD_API int          axwd_set_small_icon( const char* small_icon_file );
  AXWD_API int          axwd_set_application_name( const char* application_name );
  AXWD_API int          axwd_set_window_title( const char* window_title );
} // extern "C"
#endif // __AXE_WINDOWS_H__

/* $Id: axe_windows.h,v 1.1 2004/06/09 18:23:59 doneval Exp $ */
