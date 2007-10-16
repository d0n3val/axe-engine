/**
* @file
* Non public function headers
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      15 Jun 2004
*/
#ifndef __AXCO_CONTROL_H__
  #define __AXCO_CONTROL_H__

  #include "axco_stdafx.h"

int               call_key_repeat_events( axco_device& device, const long index );
int               check_alert( axco_alert& alert, const long index );
bool              check_event( axco_key_event& event );
axco_mouse_info*  get_mouse_device( int device_num );
void              update_mouse_mov( int device_num, int x, int y );
#endif // __AXCO_CONTROL_H__

/* $Id: axco_control.h,v 1.2 2004/08/29 18:28:44 doneval Exp $ */
