/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXPY_STATE_H__
  #define __AXPY_STATE_H__

  #include "axpy_stdafx.h"

  #define MAX_DIR_LEN 256

/**
* This class stores all data related to the state of the library
*/
class axpy_state : public axe_state
{
  public:
    char  default_directory[MAX_DIR_LEN];
    bool init;
  public:
    axpy_state() :
    axe_state()
    {
      lib_id = 'AXPY';
      strcpy_s( lib_name, LIB_NAME_LONG, "Python" );
      lib_version = 1;

      strcpy_s( default_directory, MAX_DIR_LEN, ".\\" );

      // ------------
      init = false;
    }

    ~axpy_state()
    {
      if (init == true)
      {
        axpy_finalize();
      }
    }
};
#endif // __AXPY_STATE_H__

/* $Id: axpy_state.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
