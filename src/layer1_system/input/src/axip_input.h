/**
* @file
* Internal use function declarations
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      22 May 2004
*/
#ifndef __AXIP_INPUT_H__
  #define __AXIP_INPUT_H__

  #include "axip_stdafx.h"

BOOL CALLBACK init_device_callback( const DIDEVICEINSTANCE* device_instance, void* user_data );
bool          init_mouse( const DIDEVICEINSTANCE* device_instance, axip_mouse* mouse );
bool          init_keyboard( const DIDEVICEINSTANCE* device_instance, axip_keyboard* keyboard );
int           get_device_events( axip_device *& device, const long index );
int           sort_event( axip_event& event1, axip_event& event2 );
#endif // __AXIP_INPUT_H__

/* $Id: axip_input.h,v 1.2 2004/06/11 20:14:29 doneval Exp $ */
