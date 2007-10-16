/**
* @file
* Event struct
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      25 Jul 2004
*/
#ifndef __EVENT_H__
  #define __EVENT_H__

  #include "axev_stdafx.h"

  #define AXEV_MAX_CALLBACKS    10
  #define AXEV_MAX_POST_EVENTS  10

struct event
{

  /*$1- Callback typedef -----------------------------------------------------*/
  typedef void ( *callb ) ( AXE_ID, void *, void * );

  /*$1- Properties -----------------------------------------------------------*/
  bool                                        destroyed;
  bool                                        active;
  AXE_ID                                      channel_id;
  axe_stc_array<callb, AXEV_MAX_CALLBACKS>    callbacks;
  axe_stc_array<AXE_ID, AXEV_MAX_POST_EVENTS> post_events;
  float                                       delay;
  void*                                       user_data;

  /*$1- Methods --------------------------------------------------------------*/
  event();
  ~event();
  int call(AXE_ID my_id, void* data = NULL);
};
#endif // __EVENT_H__

/* $Id: event.h,v 1.2 2004/09/20 21:28:09 doneval Exp $ */
