/**
* @file
* Chnnel struct
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#ifndef __CHANNEL_H__
  #define __CHANNEL_H__

  #include "axev_stdafx.h"

struct channel
{
  bool  active;
  bool  destroyed;

  channel::channel() :
  active( true ),
  destroyed( false ) {
  }
};
#endif // __CHANNEL_H__

/* $Id: channel.h,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
