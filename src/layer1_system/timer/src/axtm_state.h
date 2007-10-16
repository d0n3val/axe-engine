/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXTM_STATE_H__
  #define __AXTM_STATE_H__

  #include "axtm_stdafx.h"

/**
* This class stores all data related to the state of the library
*/
class axtm_state : public axe_state
{
  public:
    axe_list<axtm_timer *>  timer_list;
  public:
    axtm_state() :
    axe_state() {
      lib_id = 'AXTM';
      strcpy_s( lib_name, LIB_NAME_LONG, "Timer" );
      lib_version = 1;
    }

    ~axtm_state() {
    }
};
#endif // __AXTM_STATE_H__

/* $Id: axtm_state.h,v 1.2 2004/06/09 18:23:56 doneval Exp $ */
