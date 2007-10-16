/**
* @file
* Configure alerts to be fired on certain input events
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      11 Jun 2004
*/
#include "axco_stdafx.h"

/**
* Debug alert definition
*/
AXCO_API int axco_begin_alert( int alert_id, float min_elapsed_secs ) {

  /*$1- check current state --------------------------------------------------*/
  AXE_ASSERT( NULL == state.p_current_alert );

  /*$1- check if this alert_id already exists --------------------------------*/
  for( register long i = 0; i < state.alerts.last_item; ++i ) {
    if( state.alerts[i].id == alert_id ) {
      state.p_current_alert = &state.alerts[i];
      break;
    }
  }

  /*$1- not found case, add one alert to the list and start using it ---------*/
  if( NULL == state.p_current_alert ) {
    axco_alert alert;
    alert.id = alert_id;
    alert.active = true;
    
    state.alerts.push( alert );
    state.p_current_alert = &state.alerts.last();
  }

  state.p_current_alert->min_elapsed = (unsigned long) (min_elapsed_secs * 1000.0f);

  return( AXE_TRUE );
}

/**
* Add event to the alert
*/
AXCO_API int axco_add_event( int device_num, int key, int key_state, float elapsed_start, float elapsed_end ) {

  /*$1- check current state --------------------------------------------------*/
  AXE_ASSERT( NULL != state.p_current_alert );
  AXE_ASSERT( state.p_current_alert->num_events < MAX_EVENTS );

  /*$1- check arguments ------------------------------------------------------*/
  axip_device_info  info;
  axip_get_device( device_num, &info );

  AXE_ASSERT( key >= 0 && key < info.num_vkeys );
  AXE_ASSERT( key_state >= 0 && key_state <= 7 );
  AXE_ASSERT( elapsed_start >= 0.0f && elapsed_end >= 0.0f );

  /*$1- insert this event */
  axco_key_event  event;
  event.device_num = device_num;
  event.key = key;
  event.key_state.create(key_state, 4);
  event.elapsed_start = (unsigned long) (elapsed_start * 1000.0f);
  event.elapsed_end = (unsigned long) (elapsed_end * 1000.0f);

  int pos = state.p_current_alert->num_events++;
  state.p_current_alert->events[pos] = event;

  return( AXE_TRUE );
}

/**
* Add event to the alert
*/
AXCO_API int axco_clear_events() {

  /*$1- check current state --------------------------------------------------*/
  AXE_ASSERT( NULL != state.p_current_alert );
  state.p_current_alert->num_events = 0;

  return( AXE_TRUE );
}

/**
* End alert definition
*/
AXCO_API int axco_end_alert() {

  /*$1- check current state --------------------------------------------------*/
  AXE_ASSERT( NULL != state.p_current_alert );
  state.p_current_alert = NULL;

  return( AXE_TRUE );
}

/* $Id: axco_alerts.cpp,v 1.2 2004/07/21 22:08:52 doneval Exp $ */
