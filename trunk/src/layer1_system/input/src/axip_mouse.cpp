/**
* @file
* Class for mouse device type
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      23 May 2004
*/
#include "axip_stdafx.h"

/**
* Constructor
*/
axip_mouse::axip_mouse() : axip_device() {
  num_vkeys = MAX_MOUSE_VKEYS;
  type = AXIP_DEVICE_MOUSE;
}

/**
* Update
*/
bool axip_mouse::update(const int my_id) {
  num_events = 0;
  DIDEVICEOBJECTDATA  buffered_data[MAX_MOUSE_EVENTS];
  DWORD               buffer_size = MAX_MOUSE_EVENTS;

  /*$1- First, update DInput device ------------------------------------------*/
  if( false == update_device(buffered_data, &buffer_size) ) {
    return( false );
  }

  AXE_ASSERT( buffer_size <= MAX_KEYBOARD_EVENTS );

  /*$1- Here we flush with the contents of the buffered data from directinput */
  for( DWORD i = 0; i < buffer_size; i++ ) {
    events[i].device = my_id;
    events[i].time = buffered_data[i].dwTimeStamp;

    switch( buffered_data[i].dwOfs )
    {

      /*$1- Mouse horizontal motion --------------------------------------------*/
      case DIMOFS_X:
        events[i].type = AXIP_EVENT_AXIS_X;
        events[i].value = buffered_data[i].dwData;
        break;

      /*$1- Mouse vertical motion ----------------------------------------------*/
      case DIMOFS_Y:
        events[i].type = AXIP_EVENT_AXIS_Y;
        events[i].value = buffered_data[i].dwData;
        break;

      /*$1- Mouse roll motion --------------------------------------------------*/
      case DIMOFS_Z:
        events[i].type = AXIP_EVENT_AXIS_Z;
        events[i].value = buffered_data[i].dwData;
        break;

      /*$1- Mouse button pressed -----------------------------------------------*/
      default:
        events[i].type = ( buffered_data[i].dwData & 0x80 ) ? AXIP_EVENT_KEY_PRESSED : AXIP_EVENT_KEY_RELEASED;
        events[i].value = buffered_data[i].dwOfs;
        break;
    }
  }

  num_events = buffer_size;
  return( true );
}

/**
* Returns a certain event from the list
*/
const axip_event* axip_mouse::get_events() const {
  return(&events[0]);
}
