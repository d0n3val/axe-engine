/**
* @file
* Axe 'Plug in' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  10 Jul 2004
*/
#ifndef __AXE_PLUG_IN_H__
  #define __AXE_PLUG_IN_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXPL_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Plug-in' ..." )
  #else
    #define AXPL_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Plug-in' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXPL_NO_AUTOLINK
      #pragma comment( lib, "axe_plug_in.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axpl_states
{
  AXPL_VERSION      = 1,
  AXPL_LIBRARY_NAME,
  AXPL_LIBRARY_ID,
  AXPL_DEBUG_MODE,
  AXPL_LAST_ERROR,
  AXPL_STATE_COUNT,
};

/** @example axpl_test.cpp */
extern "C"
{

  /*$1- axpl_plug_in.cpp -----------------------------------------------------*/
  AXPL_API unsigned int axpl_get( const int query_state );
  AXPL_API unsigned int axpl_set( const int query_state, const unsigned int new_value );
  AXPL_API const char*  axpl_get_error_message( const unsigned int error_number );
  AXPL_API int          axpl_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axpl_load.cpp --------------------------------------------------------*/
  AXPL_API int          axpl_set_directory( const char* file_name );
  AXPL_API const AXE_ID axpl_load( const char* file_name );
  AXPL_API int          axpl_unload( const AXE_ID plug_in_id );
  AXPL_API const void*  axpl_get_function( const AXE_ID plug_in_id, const char* function_name );

  /*$1- axpl_query.cpp -------------------------------------------------------*/
  AXPL_API int  is_plug_in_loaded( const char* path );
} // extern "C"
#endif // __AXE_PLUG_IN_H__

/* $Id: axe_plug_in.h,v 1.2 2004/10/19 23:11:16 doneval Exp $ */
