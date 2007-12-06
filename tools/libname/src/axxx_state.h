/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXXX_STATE_H__
  #define __AXXX_STATE_H__

  #include "axxx_stdafx.h"

  #define MAX_DIR_LEN 256

/**
* This class stores all data related to the state of the library
*/
class axxx_state : public axe_state
{
  public:
    char  default_directory[MAX_DIR_LEN];
  public:
    axxx_state() :
    axe_state()
    {
      lib_id = 'AXXX';
      strcpy_s( lib_name, LIB_NAME_LONG, "Libname" );
      lib_version = 1;

      strcpy_s( default_directory, MAX_DIR_LEN, ".\\" );
    }

    ~axxx_state()
    {
    }
};
#endif // __AXXX_STATE_H__

/* $Id: axxx_state.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
