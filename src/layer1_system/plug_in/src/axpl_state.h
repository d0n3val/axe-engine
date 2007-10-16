/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXPL_STATE_H__
  #define __AXPL_STATE_H__

  #include "axpl_stdafx.h"

  #define MAX_DIR_LEN 256

/**
* This class stores all data related to the state of the library
*/
class axpl_state : public axe_state
{
  public:
    char                      default_directory[MAX_DIR_LEN];
    axe_list<loaded_plug_in>  loaded_libs;
  public:
    axpl_state() :
    axe_state()
    {
      lib_id = 'AXPL';
      strcpy_s( lib_name, LIB_NAME_LONG, "Plug-in" );
      lib_version = 1;

      strcpy_s( default_directory, MAX_DIR_LEN, ".\\" );
    }

    ~axpl_state()
    {
    }
};
#endif // __AXPL_STATE_H__

/* $Id: axpl_state.h,v 1.2 2004/10/19 23:11:16 doneval Exp $ */
