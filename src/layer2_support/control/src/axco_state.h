/*  *
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXCO_STATE_H__
  #define __AXCO_STATE_H__

  #include "axco_stdafx.h"

/**
* This class stores all data related to the state of the library
*/
class axco_state : public axe_state
{
  public:
    float                           update_rate;
    AXE_ID                          timer;
    AXE_ID                          absolute_timer;
    axco_alert*                     p_current_alert;
    axe_dyn_array<axco_alert>       alerts;
    axe_dyn_array<axco_alert_fired> alerts_fired;
    axe_dyn_array<axco_device>      devices;
    axe_dyn_array<axco_mouse_info>  mouses_info;
    int                             default_mouse;
    const axip_event*               last_event;
  public:
    axco_state() :
    axe_state() {
      lib_id = 'AXCO';
      strcpy_s( lib_name, LIB_NAME_LONG, "Control" );
      lib_version = 1;

      timer = axtm_create();
      absolute_timer = axtm_create();
      update_rate = 0.3f;
      default_mouse = -1;
    }

    ~axco_state() {
    }
};
#endif // __AXCO_STATE_H__

/* $Id: axco_state.h,v 1.5 2004/07/21 22:08:52 doneval Exp $ */
