/**
* @file
* Init and done. It uses axe input library, so it is really short
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      10 Jun 2004
*/
#include "axco_stdafx.h"

/**
* Init user input control system
*/
AXCO_API int axco_init( HWND window, HINSTANCE instance ) {
  int result = axip_init( window, instance );

  if( AXE_FALSE == result ) {
    return( AXE_FALSE );
  }

  /*$1- By default we active the first keyboard and mouse we find ------------*/
  bool  keyboard_found = false;
  bool  mouse_found = false;

  int   num_dev = axco_get_device_count();

  state.devices.resize(num_dev);

  for( register int i = 0; i < num_dev; ++i ) {
    axip_device_info  dev;
    axip_get_device( i, &dev );

    state.devices[i].keys.push(AXCO_KEY_NONE, dev.num_vkeys);

    if ( dev.type == AXIP_DEVICE_KEYBOARD ) {
      if ( false == keyboard_found ) {
        keyboard_found = true;
      } else {
        continue;
      }
    } else if (dev.type == AXIP_DEVICE_MOUSE ) {
      axco_mouse_info mouse_info;
      
      mouse_info.device_num = i;
      mouse_info.precision = 1;
      mouse_info.sensibility = 1.0f;
      mouse_info.relative_x = mouse_info.relative_y = 0.0f;
      mouse_info.x = mouse_info.y = 0;
      mouse_info.max_x = 640;
      mouse_info.max_y = 480;
      mouse_info.min_x = mouse_info.min_y = 0;

      state.mouses_info.push(mouse_info);

      if ( false == mouse_found ) {
        mouse_found = true;
        state.default_mouse = i;
      } else {
        continue;
      }
    } else {
      continue;
    }

    axco_set_device_active( i, AXE_TRUE );
  }

  AXE_ASSERT( true == keyboard_found && true == mouse_found );

  return( AXE_FALSE );
}

/**
* Finish using the lib
*/
AXCO_API int axco_done() {
  return( axip_done() );
}

/**
* Get device count found
*/
AXCO_API int axco_get_device_count() {
  return( axip_get_num_devices() );
}

/**
* Get device name
*/
AXCO_API const char* axco_get_device_name( int device_num ) {
  return( axip_get_device_name(device_num) );
}

/**
* Return device type
*/
AXCO_API axco_device_type axco_get_device_type( int device_num ) {
  axip_device_info  dev;

  axip_get_device( device_num, &dev );
  return( (axco_device_type) dev.type );
}

/**
* Return active status
*/
AXCO_API int axco_is_device_active( int device_num ) {
  axip_device_info  dev;

  axip_get_device( device_num, &dev );
  return( dev.active );
}

/**
* Set the device in "active" mode
*/
AXCO_API int axco_set_device_active( int device_num, int active ) {
  axip_set_active( device_num, active );
  return( AXE_TRUE );
}

/**
* Set the device time frame for repeat key events
*/
AXCO_API int axco_set_device_key_repeat_latency( int device_num, float latency_secs ) {
  AXE_ASSERT(device_num >= 0 && device_num <state.devices.last_item);
  AXE_ASSERT(latency_secs < 0.001f); // this latency would incurr in 1000 calls per second in repat_key situations!

  state.devices[device_num].key_repeat_latency = (unsigned long) (latency_secs * 1000.0f);
  return(AXE_TRUE);
}

/* $Id: axco_init_configure.cpp,v 1.3 2004/08/29 18:28:44 doneval Exp $ */
