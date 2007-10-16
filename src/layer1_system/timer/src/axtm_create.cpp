/**
* @file
* Axe 'timer' code to create / destroy / activate TIMERS
*/
#include "axtm_stdafx.h"

/**
* Create a new timer
*/
AXTM_API const AXE_ID axtm_create() {
  axtm_timer*   new_timer = new axtm_timer;

  return( (const AXE_ID) state.timer_list.add(new_timer) );
}

/**
* Destroys a timer
*/
AXTM_API int axtm_destroy( const AXE_ID timer_id ) {
  axe_list_item<axtm_timer *>*  item = ( axe_list_item < axtm_timer * > * ) timer_id;
#ifdef _DEBUG
  bool                          ok = state.timer_list.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  state.timer_list.del( item);

  return( AXE_TRUE );
}

/* $Id: axtm_create.cpp,v 1.2 2004/06/09 18:23:56 doneval Exp $ */
