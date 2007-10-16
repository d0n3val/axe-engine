/**
* @file
* called event struct
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#ifndef __CALLED_EVENT_H__
  #define __CALLED_EVENT_H__

  #include "axev_stdafx.h"

struct called_event
{
  AXE_ID  event_id;
  void*   data;
  double  time_frame;

  called_event::called_event() :
  event_id( 0 ),
  data( NULL ),
  time_frame( 0.0 ) {
  }
};
#endif // __CALLED_EVENT_H__

/* $Id: called_event.h,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
