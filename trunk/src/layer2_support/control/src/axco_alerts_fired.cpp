/**
* @file
* Get results from last update
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      16 Jun 2004
*/
#include "axco_stdafx.h"

/**
* Get count of fired alerts
*/
AXCO_API unsigned int axco_get_num_alerts_fired() {
  return( (unsigned int) state.alerts_fired.last_item );
}

/**
* get a fired alert
*/
AXCO_API const axco_alert_fired* axco_get_alerts_fired( unsigned int num ) {
  if ( num < (unsigned int) state.alerts_fired.last_item ) {
    return( &state.alerts_fired[num] );
  } else {
    return(NULL);
  }
}

/* $Id: axco_alerts_fired.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
