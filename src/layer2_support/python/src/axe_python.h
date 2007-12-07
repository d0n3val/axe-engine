/**
* @file
* Axe 'Python' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  06 Dec 2007
*/
#ifndef __AXE_PYTHON_H__
  #define __AXE_PYTHON_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1-  DLL proper function prefix --------------------------------------------*/
  #ifdef _USRDLL
    #define AXPY_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Python' library ..." )
  #else
    #define AXPY_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Python' library ..." )

/*$1-  Automatic .lib link ---------------------------------------------------*/
    #ifndef AXPY_NO_AUTOLINK
      #pragma comment( lib, "axe_python.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axpy_states
{
  AXPY_VERSION      = 1,
  AXPY_LIBRARY_NAME,
  AXPY_LIBRARY_ID,
  AXPY_DEBUG_MODE,
  AXPY_LAST_ERROR,
  AXPY_STATE_COUNT,
};

/** @example axpy_test.cpp */
extern "C"
{

  /*$1- axpy_python.cpp ------------------------------------------------------*/
  AXPY_API unsigned int axpy_get( const int query_state );
  AXPY_API unsigned int axpy_set( const int query_state, const unsigned int new_value );
  AXPY_API const char*  axpy_get_error_message( const unsigned int error_number );
  AXPY_API int          axpy_set_error_callback( void (*error_callback) (int, const char*, long) );

  AXPY_API int          axpy_get_int( const int query_state );
  AXPY_API int          axpy_set_int( const int query_state, const int new_value );

  /*$1- axpy_init.cpp --------------------------------------------------------*/
  AXPY_API int  axpy_init();
  AXPY_API int  axpy_finalize();

  /*$1- axpy_run.cpp ---------------------------------------------------------*/
  AXPY_API int  axpy_exec( const char* code );
  AXPY_API int  axpy_load_file( const char* file_name, const char* function_name );
} // extern "C"
#endif // __AXE_PYTHON_H__

/* $Id: axe_python.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
