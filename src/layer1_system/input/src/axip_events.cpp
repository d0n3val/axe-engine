/**
* @file
* gets all input events and return them to the user
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      23 May 2004
*/
#include "axip_stdafx.h"

/**
* Set a device to listen for events or not
*/
AXIP_API void axip_set_active( const int num_device, int active ) {
  axip_device*  dev = state.device_list[num_device];
  dev->active = ( active == AXE_TRUE ) ? true : false;
}

/**
* update all active devices and save all events ocurred from last update
*/
AXIP_API const axip_event* axip_get_events() {

  /*$1- Clear last event list ------------------------------------------------*/
  state.event_list.clear();

  /*$1- Update all active devices --------------------------------------------*/
  state.device_list.foreach( get_device_events );

  /*$1- Order event list -----------------------------------------------------*/
  state.event_list.sort( sort_event );

  /*$1- Return events --------------------------------------------------------*/
  return( state.event_list.data );
}

/**
* foreach callback to update each device
*/
int get_device_events( axip_device *& device, const long index ) {
  if( false == device->active ) {
    return( AXE_TRUE );
  }

  if( false == device->update(index) ) {
    return( AXE_TRUE );
  }

  const axip_event*   events = device->get_events();
  for( register unsigned int i = 0; i < device->num_events; ++i ) {
    state.event_list.push( events[i] );
    //AXE_INFO("Device: %d Type: %d Key:%d", events[i].device, (int)events[i].type, events[i].value);
  }

  return( AXE_TRUE );
}

/**
* Return current event count
*/
AXIP_API unsigned int axip_get_num_events() {
  return( (unsigned int) state.event_list.last_item );
}

/**
* Sort callback
*/
int sort_event( axip_event& event1, axip_event& event2 ) {
  if( event1.time > event2.time ) {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}
