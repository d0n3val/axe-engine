/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXRT_STATE_H__
  #define __AXRT_STATE_H__

  #include "axrt_stdafx.h"

  #define MAX_DIR_LEN 256

/**
* This class stores all data related to the state of the library
*/
class axrt_state : public axe_state
{
  public:
    char  default_directory[MAX_DIR_LEN];
  public:
    axrt_state() :
    axe_state()
    {
      lib_id = 'AXRT';
      strcpy_s( lib_name, LIB_NAME_LONG, "Raster" );
      lib_version = 1;

      strcpy_s( default_directory, MAX_DIR_LEN, ".\\" );
    }

    ~axrt_state()
    {
    }
};
#endif // __AXRT_STATE_H__

/* $Id: axrt_state.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
