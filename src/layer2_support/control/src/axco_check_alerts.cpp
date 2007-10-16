/**
* @file
* Check alerts and enqueue those that fired
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      10 Jul 2004
*/
#include "axco_stdafx.h"

// Disable "parameter not used" warning
#pragma warning( push )
#pragma warning( disable : 4100 )

/**
* Check alert state
*/
int check_alert( axco_alert& alert, const long index ) {
  AXE_ASSERT( NULL != state.last_event );

  if( false == alert.active || alert.num_events < 1 ) {
    return( AXE_TRUE );
  }

  /*$1- Match the event device and this alert device -------------------------*/
  if( state.last_event->device != alert.events[alert.waiting_event].device_num ) {
    return( AXE_TRUE );
  }

  /*$1- Match the event_type (pressed/released/repeat) with the alert --------*/
  axco_key_state  key_state = state.devices[state.last_event->device].keys[state.last_event->value];
  if( false == alert.events[alert.waiting_event].key_state.check_enabled(key_state, 4) ) {
    return( AXE_TRUE );
  }

  /*$1- Match event_value (key) with the alert -------------------------------*/
  if( state.last_event->value != alert.events[alert.waiting_event].key ) {

    /*$1- We receive another key, so this event become invalidated -----------*/
    alert.waiting_event = 0;
    return( AXE_TRUE );
  }

  /*$1- Check if waiting time expired ----------------------------------------*/
  unsigned long elapsed = state.last_event->time - alert.waiting_event_fired;

  if( alert.waiting_event > 0 ) {
    if(
      elapsed > alert.events[alert.waiting_event].elapsed_end ||
      elapsed < alert.events[alert.waiting_event].elapsed_start ) {
      alert.waiting_event = 0;
      return( AXE_TRUE );
    }
  } else {
    if( elapsed < alert.min_elapsed ) {
      return( AXE_TRUE );
    }
  }

  /*$1- Save the time when this event ocurred ----------------------------------*/
  alert.waiting_event_fired = state.last_event->time;

  /*$1- If this is the last event to check, fire the alert -------------------*/
  if( alert.waiting_event == alert.num_events - 1 ) {
    axco_alert_fired  alert_fired;
    alert_fired.alert_id = alert.id;
    state.alerts_fired.push( alert_fired );
    alert.waiting_event = 0;
  }

  return( AXE_TRUE );
}

/**
* Rotate all device keys
*/
int call_key_repeat_events( axco_device& device, const long index ) {
  for( register int i = 0; i < device.keys.last_item; ++i ) {
    if( AXCO_KEY_REPEAT == device.keys[i] ) {
      axip_event  event;
      event.device = index;
      event.time = 0;
      event.value = i;
      state.last_event = &event;
      state.alerts.foreach( check_alert );
    }
  }

  return( AXE_TRUE );
}

/**
* Check repeat key events and check alerts that could be fired
*/
int check_repeat_keys( unsigned long time_frame ) {
  return(0);
}

// enable previous warning state
#pragma warning( pop )

/* $Id: axco_check_alerts.cpp,v 1.2 2004/08/29 18:28:44 doneval Exp $ */
