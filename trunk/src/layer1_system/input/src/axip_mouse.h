/*
* @file
* Data that describes a single mouse device
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      23 May 2004
*/
#ifndef __AXIP_MOUSE_H__
  #define __AXIP_MOUSE_H__

  #include "axip_stdafx.h"

  #define MAX_MOUSE_VKEYS 8

/**
* Keyboard device specialization
*/
class axip_mouse : public axip_device
{
  public:
    DWORD       vkeys[MAX_MOUSE_VKEYS];
    axip_event  events[MAX_MOUSE_EVENTS];
  public:
    axip_mouse();
    bool                update( const int my_id );
    const axip_event*   get_events() const;
};
#endif // __AXIP_MOUSE_H__

/* $Id: axip_mouse.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
