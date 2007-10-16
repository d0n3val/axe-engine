/**
* @file
* Update events qeue
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#include "axev_stdafx.h"

/**
* QuickSort callback to order called events by time
*/
int sort_called_events( called_event& event_1, called_event& event_2 ) {
  if( event_1.time_frame > event_2.time_frame ) {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/**
* Update events qeue
*/
AXEV_API int axev_update( float elapsed_seconds ) {
  float elapsed = axtm_start( state.timer_id );
  if( elapsed_seconds >= 0.0f ) {
    elapsed = elapsed_seconds;
  }

  state.total_time += (double) elapsed;

  /*$1- Order the list by time frame -----------------------------------------*/
  state.called_events.sort( sort_called_events );

  /*$1- Now call each event --------------------------------------------------*/
  bool          found = false;
  register long i = 0;
  for( ; i < state.called_events.last_item; ++i ) {
    if( state.called_events[i].time_frame < state.total_time ) {
      AXE_ID  id = state.called_events[i].event_id;
      state.events[id].call( id, state.called_events[i].data );
      found = true;
    } else {
      break;
    }
  }

  /*$1- Erase all obsolete data ----------------------------------------------*/
  if( true == found ) {
    state.called_events.remove(0, i);
  }

  /*$1- Empty called events --------------------------------------------------*/
  return( AXE_TRUE );
}

/**
* Add event to events qeue
*/
AXEV_API int axev_call_event( AXE_ID event_id, void* data, float delay_in_seconds ) {
  AXE_ASSERT( state.events.exist(event_id) );

  called_event  new_event;

  new_event.data = data;
  new_event.event_id = event_id;
  new_event.time_frame = state.total_time +
    axtm_elapsed( state.timer_id ) +
    delay_in_seconds +
    state.events[event_id].delay;

  state.called_events.push( new_event );
  return( AXE_TRUE );
}

/* $Id: axev_update.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
