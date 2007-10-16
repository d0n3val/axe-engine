/**
* @file
* Axe 'timer' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  19 Dec 2004
*/
#ifndef __AXE_TIMER_H__
  #define __AXE_TIMER_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXTM_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Timer' ..." )
  #else
    #define AXTM_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Timer' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXTM_NO_AUTOLINK
      #pragma comment( lib, "axe_timer.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axtm_states
{
  AXTM_VERSION      = 1,
  AXTM_LIBRARY_NAME,
  AXTM_LIBRARY_ID,
  AXTM_DEBUG_MODE,
  AXTM_LAST_ERROR,
  AXTM_STATE_COUNT,
};

/** @example axtm_test.cpp */
extern "C"
{

  /*$1-axtm_timer.cpp --------------------------------------------------------*/
  AXTM_API unsigned int axtm_get( const int query_state );
  AXTM_API unsigned int axtm_set( const int query_state, const unsigned int new_value );
  AXTM_API const char*  axtm_get_error_message( const unsigned int error_number );
  AXTM_API int          axtm_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axtm_create.cpp ------------------------------------------------------*/
  AXTM_API const AXE_ID axtm_create();
  AXTM_API int          axtm_destroy( const AXE_ID timer_id );

  /*$1- axtm_manage.cpp ------------------------------------------------------*/
  AXTM_API float        axtm_start( const AXE_ID timer_id );
  AXTM_API float        axtm_elapsed( const AXE_ID timer_id );
  AXTM_API float        axtm_elapsed_from_mark( const AXE_ID timer_id, const bool reset_mark = true );
  AXTM_API unsigned int axtm_elapsed_ticks( const AXE_ID timer_id );
  AXTM_API float        axtm_stop( const AXE_ID timer_id );
} // extern "C"
#endif // __AXE_TIMER_H__

/* $Id: axe_timer.h,v 1.3 2004/09/20 21:28:10 doneval Exp $ */
