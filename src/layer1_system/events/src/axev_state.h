/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXEV_STATE_H__
  #define __AXEV_STATE_H__

  #include "axev_stdafx.h"

/**
* This class stores all data related to the state of the library
*/
class axev_state : public axe_state
{
  public:
    axe_dyn_array<event>        events;
    axe_dyn_array<channel>      channels;
    axe_dyn_array<called_event> called_events;
    AXE_ID                      timer_id;
    double                      total_time;
  public:
    axev_state() :
    axe_state() {
      lib_id = 'AXEV';
      strcpy_s( lib_name, LIB_NAME_LONG, "Events" );
      lib_version = 1;

      timer_id = axtm_create();
      total_time = 0.0;

      /*$1- Create a dummy channel (id = 0) */
      axev_create_channel();

      /*$1- Create a dummy event (id = 0) */
      axev_create_event();
    }

    ~axev_state() {
    }
};
#endif // __AXEV_STATE_H__

/* $Id: axev_state.h,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
