/**
* @file
* Update and collect data from input lib
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      10 Jun 2004
*/
#include "axco_stdafx.h"

/**
* Change the update rate of the system
*/
AXCO_API int axco_set_update_rate( const float update_rate_in_seconds )
{
  AXE_ASSERT( update_rate_in_seconds > 0.0f );
  state.update_rate = update_rate_in_seconds;
  return( AXE_TRUE );
}

/**
* Update the input data
*/
AXCO_API int axco_update()
{

  /*$1- first check if update_rate time has passed ---------------------------*/
  if( axtm_elapsed(state.timer) < state.update_rate )
  {
    return( AXE_FALSE );
  }

  /*$1- Reset update timer ---------------------------------------------------*/
  axtm_start( state.timer );

  /*$1- Clear alerts fired previously ----------------------------------------*/
  state.alerts_fired.clear();

  /*$1- get input events -----------------------------------------------------*/
  const axip_event*   events = axip_get_events();
  unsigned int        num_events = axip_get_num_events();
  axip_device_info    info;

  /*$1- Update data from input events ----------------------------------------*/
  for( register unsigned int i = 0; i < num_events; ++i )
  {
    int dev_id = events[i].device;
    axip_get_device( dev_id, &info );

    int key = events[i].value;
    if( info.type == AXIP_DEVICE_MOUSE )
    {
      if( AXIP_EVENT_KEY_PRESSED == events[i].type || AXIP_EVENT_KEY_RELEASED == events[i].type )
      {
        key -= 12;
      }
    }

    state.last_event = &events[i];

    switch( events[i].type )
    {
      case AXIP_EVENT_KEY_PRESSED:
        state.devices[dev_id].keys[key] = AXCO_KEY_PRESS;
        state.alerts.foreach( check_alert );
        state.devices[dev_id].keys[key] = AXCO_KEY_REPEAT;
        break;

      case AXIP_EVENT_KEY_RELEASED:
        state.devices[dev_id].keys[key] = AXCO_KEY_RELEASE;
        state.alerts.foreach( check_alert );
        state.devices[dev_id].keys[key] = AXCO_KEY_NONE;
        break;

      case AXIP_EVENT_AXIS_X:
        update_mouse_mov( events[i].device, events[i].value, 0 );
        break;

      case AXIP_EVENT_AXIS_Y:
        update_mouse_mov( events[i].device, 0, events[i].value );
        break;

      case AXIP_EVENT_AXIS_Z:
        break;
    }
  }

  /*$1- check for repeat key events ------------------------------------------*/
  state.devices.foreach( call_key_repeat_events );
  state.last_event = NULL;

  return( AXE_TRUE );
}

/**
* Check if a certain key is pressed
*/
AXCO_API int axco_is_key_pressed( int device_num, int key )
{
  axip_device_info  dev;

  axip_get_device( device_num, &dev );
  if( dev.active == AXE_TRUE && state.devices[device_num].keys[key] == AXCO_KEY_REPEAT )
  {
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/* $Id: axco_update.cpp,v 1.3 2004/09/20 21:28:11 doneval Exp $ */
