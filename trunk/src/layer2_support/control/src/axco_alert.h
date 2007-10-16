/**
* @file
* Alert definition
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      11 Jun 2004
*/
#ifndef __AXCO_ALERT_H__
  #define __AXCO_ALERT_H__

  #include "axco_stdafx.h"

  #define MAX_EVENTS  10

/**
* Single key event
*/
struct axco_key_event
{
  int           device_num;
  unsigned int  key;
  axe_bitset<4> key_state;
  unsigned long elapsed_start;
  unsigned long elapsed_end;

  axco_key_event::axco_key_event() :
  device_num( -1 ),
  key( 0 ),
  elapsed_start( 0 ),
  elapsed_end( 0 ) {
    key_state.zero();
  }
};

/**
* complete alert
*/
struct axco_alert
{
  int                                       id;
  unsigned int                              num_events;
  bool                                      active;
  axe_stc_array<axco_key_event, MAX_EVENTS> events;
  unsigned int                              waiting_event;
  unsigned long                             waiting_event_fired;
  unsigned long                             min_elapsed;

  axco_alert::axco_alert() :
  id( 0 ),
  waiting_event( 0 ),
  num_events( 0 ),
  waiting_event_fired( 0 ),
  active( false ),
  min_elapsed(0) {
  }
};
#endif // __AXCO_ALERT_H__

/* $Id: axco_alert.h,v 1.2 2004/07/21 22:08:52 doneval Exp $ */
