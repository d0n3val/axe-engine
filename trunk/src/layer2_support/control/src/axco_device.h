/**
* @file
* manages a single input device
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      14 Jun 2004
*/
#ifndef __AXCO_DEVICE_H__
  #define __AXCO_DEVICE_H__

  #include "axco_stdafx.h"

struct axco_device
{
  unsigned long                 key_repeat_latency;
  axe_dyn_array<axco_key_state> keys;

  axco_device::axco_device() :
  key_repeat_latency( 0 ) {
  }
};
#endif // __AXCO_DEVICE_H__

/* $Id: axco_device.h,v 1.2 2004/07/21 22:08:52 doneval Exp $ */
