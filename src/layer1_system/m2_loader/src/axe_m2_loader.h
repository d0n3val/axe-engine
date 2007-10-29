/**
* @file
* Axe 'M2 model format loader' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  14 Oct 2007
*/
#ifndef __AXE_M2_LOADER_H__
  #define __AXE_M2_LOADER_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1-  DLL proper function prefix --------------------------------------------*/
  #ifdef _USRDLL
    #define AXM2_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'm2_loader' library ..." )
  #else
    #define AXM2_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'm2_loader' library ..." )

/*$1-  Automatic .lib link ---------------------------------------------------*/
    #ifndef AXM2_NO_AUTOLINK
#pragma comment( lib, "axe_m2_loader.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axm2_states
{
  AXM2_VERSION      = 1,
  AXM2_LIBRARY_NAME,
  AXM2_LIBRARY_ID,
  AXM2_DEBUG_MODE,
  AXM2_LAST_ERROR,
  AXM2_STATE_COUNT,
};

/** @example axm2_test.cpp */
extern "C"
{

  /*$1- axpl_plug_in.cpp -----------------------------------------------------*/
  AXM2_API unsigned int axm2_get( const int query_state );
  AXM2_API unsigned int axm2_set( const int query_state, const unsigned int new_value );
  AXM2_API const char*  axm2_get_error_message( const unsigned int error_number );
  AXM2_API int          axm2_set_error_callback( void (*error_callback) (int, const char*, long) );

  AXM2_API int          axm2_get_int( const int query_state );
  AXM2_API int          axm2_set_int( const int query_state, const int new_value );
} // extern "C"
#endif // __AXE_M2_LOADER_H__

/* $Id: axe_raster.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
