/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXM2_STATE_H__
  #define __AXM2_STATE_H__

  #include "axm2_stdafx.h"

  #define MAX_DIR_LEN 256

/**
* This class stores all data related to the state of the library
*/
class axm2_state : public axe_state
{
  public:
    char  default_directory[MAX_DIR_LEN];
  public:
    axm2_state() :
    axe_state()
    {
      lib_id = 'AXM2';
      strcpy_s( lib_name, LIB_NAME_LONG, "m2_loader" );
      lib_version = 1;

      strcpy_s( default_directory, MAX_DIR_LEN, ".\\" );
    }

    ~axm2_state()
    {
    }
};
#endif // __AXM2_STATE_H__

/* $Id: axm2_state.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
