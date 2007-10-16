/**
* @file
* 
* @author    Carlos Fuentes
* @date      22 Aug 2004
*/
#ifndef __AXSB_STATE_H__
  #define __AXSB_STATE_H__

  #include "axsb_stdafx.h"

/**
* This class stores all data related to the state of the library
*/
class axsb_state : public axe_state
{
  public:
    axsb_buffer_id  default_buffer;
  public:
    axsb_state() :
    axe_state()
    {
      default_buffer = -1;
    }

    ~axsb_state()
    {
    }
};
#endif // __AXSB_STATE_H__

/* $Id: axsb_state.h,v 1.2 2004/08/23 21:26:11 ilgenio Exp $ */
