/**
* @file
* Axe 'timer' code to create / destroy / activate TIMERS
*/
#include "axtm_stdafx.h"

/**
* Reset a timer
*/
AXTM_API float axtm_start( const AXE_ID timer_id ) {
  axe_list_item<axtm_timer *>*  item = ( axe_list_item < axtm_timer * > * ) timer_id;
#ifdef _DEBUG
  bool                          ok = state.timer_list.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  return( item->data->start() );
}

/**
* Gets elapsed time in seconds
*/
AXTM_API float axtm_elapsed( const AXE_ID timer_id ) {
  axe_list_item<axtm_timer *>*  item = ( axe_list_item < axtm_timer * > * ) timer_id;
#ifdef _DEBUG
  bool                          ok = state.timer_list.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  return( item->data->elapsed() );
}

/**
* Gets elapsed time in seconds from last mark
*/
AXTM_API float axtm_elapsed_from_mark( const AXE_ID timer_id, const bool reset_mark ) {
  axe_list_item<axtm_timer *>*  item = ( axe_list_item < axtm_timer * > * ) timer_id;
#ifdef _DEBUG
  bool                          ok = state.timer_list.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  return( item->data->mark_elapsed(reset_mark) );
}

/**
* Gets elapsed time in CPU ticks
*/
AXTM_API unsigned int axtm_elapsed_ticks( const AXE_ID timer_id ) {
  axe_list_item<axtm_timer *>*  item = ( axe_list_item < axtm_timer * > * ) timer_id;
#ifdef _DEBUG
  bool                          ok = state.timer_list.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  return( item->data->elapsed_ticks() );
}

/**
* Stops a timer
*/
AXTM_API float axtm_stop( const AXE_ID timer_id ) {
  axe_list_item<axtm_timer *>*  item = ( axe_list_item < axtm_timer * > * ) timer_id;
#ifdef _DEBUG
  bool                          ok = state.timer_list.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  return( item->data->stop() );
}

/* $Id: axtm_manage.cpp,v 1.2 2004/09/20 21:28:10 doneval Exp $ */
