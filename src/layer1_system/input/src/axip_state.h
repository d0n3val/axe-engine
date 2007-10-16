/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXIP_STATE_H__
  #define __AXIP_STATE_H__

  #include "axip_stdafx.h"

/**
* This class stores all data related to the state of the library
*/
class axip_state : public axe_state
{
  public:
    bool                      init;
    HWND                      window;
    HINSTANCE                 instance;
    LPDIRECTINPUT8            dinput;
    axe_list<axip_device*>    device_list;
    axe_dyn_array<axip_event> event_list;
  public:
    axip_state() :
    axe_state() {
      lib_id = 'AXIP';
      strcpy_s( lib_name, LIB_NAME_LONG, "Input" );
      lib_version = 1;

      init = false;
      window = NULL;
      instance = NULL;
      dinput = NULL;
    }

    ~axip_state() {
      if ( true == init ) {
        axip_done();
      }
    }
};
#endif // __AXIP_STATE_H__

/* $Id: axip_state.h,v 1.2 2004/06/11 20:14:29 doneval Exp $ */
