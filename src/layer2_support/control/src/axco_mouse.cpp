/**
* @file
* Mouse functions
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      03 Jul 2004
*/
#include "axco_stdafx.h"

/**
* Set box for mouse movement
*/
AXCO_API int axco_set_mouse_limits( int left, int top, int right, int bottom, int device_num ) {
  AXE_ASSERT(left > right && top > bottom);

  axco_mouse_info* mouse_info = get_mouse_device(device_num);

  mouse_info->min_x = left;
  mouse_info->max_x = right;
  mouse_info->min_y = bottom;
  mouse_info->max_y = top;

  axco_set_mouse_pos(mouse_info->x, mouse_info->y, device_num);

  return( AXE_TRUE );
}

/**
* Set mouse position in absolute coords
*/
AXCO_API int axco_set_mouse_pos( int x, int y, int device_num ) {
  axco_mouse_info* mouse_info = get_mouse_device(device_num);
  
  mouse_info->x = x;
  mouse_info->y = y;

  mouse_info->x = min(mouse_info->max_x, mouse_info->x);
  mouse_info->x = max(mouse_info->min_x, mouse_info->x);
  
  mouse_info->y = min(mouse_info->max_y, mouse_info->y);
  mouse_info->y = max(mouse_info->min_y, mouse_info->y);

  mouse_info->relative_x = (float) (mouse_info->max_x - mouse_info->min_x) / (float) x;
  mouse_info->relative_y = (float) (mouse_info->max_y - mouse_info->min_y) / (float) y;

  return( AXE_TRUE );
}

/**
* Set mouse in relative coordinates [0..1]
*/
AXCO_API int axco_set_mouse_relative_pos( float x, float y, int device_num ) {
  axco_mouse_info* mouse_info = get_mouse_device(device_num);

  axco_set_mouse_pos(
    (int) ((mouse_info->max_x - mouse_info->min_x) * x),
    (int) ((mouse_info->max_y - mouse_info->min_y) * y),
    device_num);

  return( AXE_TRUE );
}

/**
* Get mouse info, like position, sensibility, etc ...
*/
AXCO_API axco_mouse_info axco_get_mouse_info( int device_num ) {
  return( *get_mouse_device(device_num) );
}

/**
* Set mouse sensibility. Movement will be multiplied for this factor.
*/
AXCO_API int axco_set_mouse_sensibility( float sensibility, int device_num ) {
  AXE_ASSERT(sensibility >= 0.0f);
  axco_mouse_info* mouse_info = get_mouse_device(device_num);

  mouse_info->sensibility = sensibility;
  return( AXE_TRUE );
}

/**
* Set mouse precision. Less events callback will be produced if this number raises. Max precision = 1
*/
AXCO_API int axco_set_mouse_precision( int precision, int device_num ) {
  AXE_ASSERT(precision >= 0);
  axco_mouse_info* mouse_info = get_mouse_device(device_num);

  mouse_info->precision = precision;
  return( AXE_TRUE );
}


/**
* Search a mouse device
*/
axco_mouse_info* get_mouse_device(int device_num) {
  AXE_ASSERT( device_num >= 0 || state.default_mouse >= 0 );
  
  int dev;

  if( device_num < 0 ) {
    dev = state.default_mouse;
  } else {
    axip_device_info  info;
    axip_get_device( device_num, &info );

    AXE_ASSERT( AXIP_DEVICE_MOUSE == info.type );
    AXE_ASSERT( AXE_TRUE == info.active );
    dev = device_num;
  }

  for( register int i = 0; i < state.mouses_info.last_item; ++i ) {
  	if ( dev == state.mouses_info[i].device_num ) {
      return(&state.mouses_info[i]);
  	}
  }
  
  AXE_ASSERT(0 && "Mouse device not found");
  return(NULL);
}

/* $Id: axco_mouse.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
