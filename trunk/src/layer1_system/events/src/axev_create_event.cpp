/**
* @file
* Cretae and configure events
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#include "axev_stdafx.h"

/**
* Create a new event
*/
AXEV_API AXE_ID axev_create_event( AXE_ID channel_id ) {
  AXE_ASSERT( state.channels.exist(channel_id) );

  event   my_event;
  event*  p_event = &my_event;
  int     found = -1;

  for( register int i = 0; i < state.events.last_item; ++i ) {
    if( true == state.events[i].destroyed ) {
      p_event = &state.events[i];
      found = i;
      break;
    }
  }

  p_event->channel_id = channel_id;
  p_event->active = true;
  p_event->destroyed = false;

  if( found >= 0 ) {
    return( found );
  }

  state.events.push( *p_event );
  return( state.events.last_item-1 );
}

/**
* Destroy existing event
*/
AXEV_API int axev_destroy_event( AXE_ID event_id ) {
  AXE_ASSERT( state.events.exist(event_id) );
  AXE_ASSERT( false == state.events[event_id].destroyed );

  state.events[event_id].destroyed = true;

  return( AXE_TRUE );
}

/**
* Add a callback funtion to an event
*/
AXEV_API int axev_add_event_callback( AXE_ID event_id, void (*event_callback) (AXE_ID, void *, void *) ) {
  AXE_ASSERT( state.events.exist(event_id) );
  AXE_ASSERT( false == state.events[event_id].destroyed );
  AXE_ASSERT( NULL != event_callback );

  bool  found = false;
  for( register int i = 0; i < state.events[event_id].callbacks.size; ++i ) {
    if( NULL == state.events[event_id].callbacks[i] ) {
      found = true;
      state.events[event_id].callbacks[i] = event_callback;
      break;
    }
  }

  AXE_ASSERT( found );  // check max callback reached
  return( AXE_TRUE );
}

/**
* Add a new event that will be called if this event ocurrs (event chaining)
*/
AXEV_API int axev_add_event_post( AXE_ID event_id, AXE_ID post_event_id ) {
  AXE_ASSERT( state.events.exist(event_id) );
  AXE_ASSERT( state.events.exist(post_event_id) );
  AXE_ASSERT( false == state.events[event_id].destroyed );

  bool  found = false;
  for( register int i = 0; i < state.events[event_id].post_events.size; ++i ) {
    if( 0 == state.events[event_id].post_events[i] ) {
      found = true;
      state.events[event_id].post_events[i] = post_event_id;
      break;
    }
  }

  AXE_ASSERT( found );  // check max callback reached
  return( AXE_TRUE );
}

/**
* Standar delay when this event is called
*/
AXEV_API int axev_set_event_delay( AXE_ID event_id, float seconds ) {
  AXE_ASSERT( state.events.exist(event_id) );
  AXE_ASSERT( false == state.events[event_id].destroyed );
  AXE_ASSERT( seconds >= 0.0f );

  state.events[event_id].delay = seconds;

  return( AXE_TRUE );
}

/**
* Activates / Desactivates an event
*/
AXEV_API int axev_set_event_active( AXE_ID event_id, int active ) {
  AXE_ASSERT( state.events.exist(event_id) );
  AXE_ASSERT( false == state.events[event_id].destroyed );

  state.events[event_id].active = AXE_TO_BOOL( active );

  return( AXE_TRUE );
}

/**
* Set event user data that will sent in each defined callback
*/
AXEV_API int axev_set_event_userdata( AXE_ID event_id, const void* data, size_t data_size ) {
  AXE_ASSERT( state.events.exist(event_id) );

  AXE_FREE(state.events[event_id].user_data);

  if ( NULL == data ) {
    return(AXE_TRUE);
  }
  
  state.events[event_id].user_data = malloc(data_size);
  memcpy(state.events[event_id].user_data, data, data_size);

  return(AXE_TRUE);
}

/* $Id: axev_create_event.cpp,v 1.2 2004/09/20 21:28:09 doneval Exp $ */
