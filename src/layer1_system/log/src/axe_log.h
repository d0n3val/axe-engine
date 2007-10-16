/**
* @file
* Axe 'log' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  22 Nov 2003
*/
#ifndef __AXE_LOG_H__
  #define __AXE_LOG_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXLG_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Log' ..." )
  #else
    #define AXLG_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Log' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXLG_NO_AUTOLINK
      #pragma comment( lib, "axe_log.lib" )
    #endif
  #endif

/*$1- Shortcut defines, sorry for the odd of this macro ----------------------*/
  #define AXE_INFO    axlg_log_ref( __FILE__, __LINE__, AXLG_INFO ), axlg_log
  #define AXE_WARNING axlg_log_ref( __FILE__, __LINE__, AXLG_WARNING ), axlg_log
  #define AXE_ERROR   axlg_log_ref( __FILE__, __LINE__, AXLG_ERROR ), axlg_log

/*$1-States for this lib -----------------------------------------------------*/
enum axlg_states
{
  AXLG_VERSION      = 1,
  AXLG_LIBRARY_NAME,
  AXLG_LIBRARY_ID,
  AXLG_DEBUG_MODE,
  AXLG_LAST_ERROR,
  AXLG_STATE_COUNT
};

enum axlg_priority
{
  AXLG_INFO         = 0,
  AXLG_WARNING,
  AXLG_ERROR
};

/** @example axlg_test.cpp */
extern "C"
{

  /*$1- axlg_log.cpp ---------------------------------------------------------*/
  AXLG_API unsigned int axlg_get( const int query_state );
  AXLG_API unsigned int axlg_set( const int query_state, const unsigned int new_value );
  AXLG_API const char*  axlg_get_error_message( const unsigned int error_number );
  AXLG_API int          axlg_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axlg_add.cpp ---------------------------------------------------------*/
  AXLG_API int  axlg_log( const char* format, ... );
  AXLG_API int  axlg_log_ref( const char* file, const unsigned long line, axlg_priority priority );

  /*$1- axlg_filter.cpp ------------------------------------------------------*/
  AXLG_API void axlg_set_filter( const char* filter );
  AXLG_API void axlg_remove_filter();
} // extern "C"
#endif // __AXE_LOG_H__

/* $Id: axe_log.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
