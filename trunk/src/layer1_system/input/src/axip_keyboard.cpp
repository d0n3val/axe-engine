/**
* @file
* Class for keyboard device type
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      23 May 2004
*/
#include "axip_stdafx.h"

/**
* Constructor
*/
axip_keyboard::axip_keyboard() : axip_device() {
  num_vkeys = MAX_KEYBOARD_VKEYS;
  type = AXIP_DEVICE_KEYBOARD;
}

/**
* Update
*/
bool axip_keyboard::update(const int my_id) {

  /*$1- First, clear previuos events -----------------------------------------*/
  num_events = 0;

  //! Receives buffered data
  DIDEVICEOBJECTDATA  buffered_data[MAX_KEYBOARD_EVENTS];
  DWORD               buffer_size = MAX_KEYBOARD_EVENTS;

  /*$1- First, update DInput device ------------------------------------------*/
  if( false == update_device(buffered_data, &buffer_size) ) {
    return( false );
  }

  AXE_ASSERT(buffer_size <= MAX_KEYBOARD_EVENTS);

  /*$1- Here we flush with the contents of the buffered data from directinput */
  for( DWORD i = 0; i < buffer_size; i++ ) {
    events[i].device = my_id;
    events[i].type = ( buffered_data[i].dwData & 0x80 ) ? AXIP_EVENT_KEY_PRESSED : AXIP_EVENT_KEY_RELEASED;
    events[i].value = buffered_data[i].dwOfs;
    events[i].time = buffered_data[i].dwTimeStamp;
  }

  num_events = buffer_size;
  return( true );
}

/**
* Returns list of last events
*/
const axip_event* axip_keyboard::get_events() const {
  return(&events[0]);
}