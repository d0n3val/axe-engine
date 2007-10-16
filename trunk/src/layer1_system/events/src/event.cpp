/**
* @file
* Event struct methods
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#include "axev_stdafx.h"

/**
* Constructor
*/
event::event() : destroyed( false ), active( true ), channel_id( 0 ), delay( 0.0f ), user_data(NULL) {
  for( register int i = 0; i < callbacks.size; ++i ) {
    callbacks[i] = NULL;
  }

  for( register int i = 0; i < post_events.size; ++i ) {
    post_events[i] = 0;
  }
}

/**
* Destructor
*/
event::~event() {
  AXE_FREE(user_data);
}

/**
* Call this event
*/
int event::call( AXE_ID my_id, void* data ) {
  AXE_ASSERT( my_id > 0 );

  for( register int i = 0; i < callbacks.size; ++i ) {
    if( NULL != callbacks[i] ) {
      callbacks[i]( my_id, user_data, data );
    }
  }

  for( register int i = 0; i < post_events.size; ++i ) {
    if( 0 != post_events[i] ) {

      // Still to define, what "data" has to be sent ?
      AXE_ID  id = post_events[i];

      state.events[id].call( id, data );
    }
  }

  return( AXE_TRUE );
}

/* $Id: event.cpp,v 1.2 2004/09/20 21:28:09 doneval Exp $ */
