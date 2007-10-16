/**
* @file
* Axe 'events' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  10 Jul 2004
*/
#ifndef __AXE_EVENTS_H__
  #define __AXE_EVENTS_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXEV_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Events' ..." )
  #else
    #define AXEV_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Events' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXEV_NO_AUTOLINK
      #pragma comment( lib, "axe_events.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axev_states
{
  AXEV_VERSION      = 1,
  AXEV_LIBRARY_NAME,
  AXEV_LIBRARY_ID,
  AXEV_DEBUG_MODE,
  AXEV_LAST_ERROR,
  AXEV_STATE_COUNT,
};

/** @example axev_test.cpp */
extern "C"
{

  /*$1- axev_events.cpp ------------------------------------------------------*/
  AXEV_API unsigned int axev_get( const int query_state );
  AXEV_API unsigned int axev_set( const int query_state, const unsigned int new_value );
  AXEV_API const char*  axev_get_error_message( const unsigned int error_number );
  AXEV_API int          axev_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axev_create_event.cpp ------------------------------------------------*/
  AXEV_API AXE_ID axev_create_event( AXE_ID channel_id = 0 );
  AXEV_API int    axev_destroy_event( AXE_ID event_id );
  AXEV_API int    axev_add_event_callback( AXE_ID event_id, void (*event_callback) (AXE_ID, void *, void *) );
  AXEV_API int    axev_add_event_post( AXE_ID event_id, AXE_ID post_event_id );
  AXEV_API int    axev_set_event_delay( AXE_ID event_id, float seconds );
  AXEV_API int    axev_set_event_active( AXE_ID event_id, int active );
  AXEV_API int    axev_set_event_userdata( AXE_ID event_id, const void* data, size_t data_size );

  /*$1- axev_channel.cpp -----------------------------------------------------*/
  AXEV_API AXE_ID axev_create_channel();
  AXEV_API int    axev_destroy_channel( AXE_ID channel_id );
  AXEV_API int    axev_channel_active( AXE_ID channel_id, int active );

  /*$1- axev_update.cpp ------------------------------------------------------*/
  AXEV_API int  axev_update( float elapsed_seconds = -1.0f );
  AXEV_API int  axev_call_event( AXE_ID event_id, void* data = NULL, float delay_in_seconds = 0.0f );

  /*$1- axev_record.cpp ------------------------------------------------------*/
  /*
  AXEV_API int    axev_start_recording( AXE_ID channel_id = 0 );
  AXEV_API int    axev_stop_recording( AXE_ID channel_id = 0 );
  AXEV_API void*  axev_get_recorded_data();
  AXEV_API void*  axev_empty_recorded_data();*/

  /*$1- axev_play.cpp --------------------------------------------------------*/
  /*AXEV_API int  axev_load_sequence( void* data );
  AXEV_API int  axev_start_sequence( float start_time = 0.0f );
  AXEV_API int  axev_stop_sequence();*/
} // extern "C"
#endif // __AXE_EVENTS_H__

/* $Id: axe_events.h,v 1.2 2004/09/20 21:28:09 doneval Exp $ */
