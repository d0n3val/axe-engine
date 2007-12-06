/**
* @file
* Axe 'Libname' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  14 Oct 2007
*/
#ifndef __AXE_LIBNAME_H__
  #define __AXE_LIBNAME_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1-  DLL proper function prefix --------------------------------------------*/
  #ifdef _USRDLL
    #define AXXX_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Libname' library ..." )
  #else
    #define AXXX_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Libname' library ..." )

/*$1-  Automatic .lib link ---------------------------------------------------*/
    #ifndef AXXX_NO_AUTOLINK
      #pragma comment( lib, "axe_libname.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axxx_states
{
  AXXX_VERSION      = 1,
  AXXX_LIBRARY_NAME,
  AXXX_LIBRARY_ID,
  AXXX_DEBUG_MODE,
  AXXX_LAST_ERROR,
  AXXX_STATE_COUNT,
};

/** @example axxx_test.cpp */
extern "C"
{

  /*$1- axpl_plug_in.cpp -----------------------------------------------------*/
  AXXX_API unsigned int axxx_get( const int query_state );
  AXXX_API unsigned int axxx_set( const int query_state, const unsigned int new_value );
  AXXX_API const char*  axxx_get_error_message( const unsigned int error_number );
  AXXX_API int          axxx_set_error_callback( void (*error_callback) (int, const char*, long) );

  AXXX_API int          axxx_get_int( const int query_state );
  AXXX_API int          axxx_set_int( const int query_state, const int new_value );
} // extern "C"
#endif // __AXE_LIBNAME_H__

/* $Id: axe_libname.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
