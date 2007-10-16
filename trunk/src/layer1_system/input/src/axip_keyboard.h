/*
* @file
* Data that describes a single keyboard device
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      23 May 2004
*/
#ifndef __AXIP_KEYBOARD_H__
  #define __AXIP_KEYBOARD_H__

  #include "axip_stdafx.h"

  #define MAX_KEYBOARD_VKEYS  256

/**
* Keyboard device specialization
*/
class axip_keyboard : public axip_device
{
  public:
    DWORD       vkeys[MAX_KEYBOARD_VKEYS];
    axip_event  events[MAX_KEYBOARD_EVENTS];
  public:
    axip_keyboard();
    bool                update( const int my_id );
    const axip_event*   get_events() const;
};
#endif // __AXIP_KEYBOARD_H__

/* $Id: axip_keyboard.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
