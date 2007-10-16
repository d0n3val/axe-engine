/**
* @file
* _state class include header
* Used to store all data about current library state
*/
#ifndef __AXFS_STATE_H__
  #define __AXFS_STATE_H__

  #include "axfs_stdafx.h"
  
/**
* This class stores all data related to the state of the library
*/
class axfs_state : public axe_state
{
  public:
    axe_list<axfs_file *> file_list;              /// stores all pointers to opened files
    char                  current_dir[_MAX_PATH]; /// stores current directory
  public:
    axfs_state() :
    axe_state() {
      lib_id = 'AXFS';
      strcpy_s(lib_name, LIB_NAME_LONG, "File System");
      lib_version = 1;
    }

    ~axfs_state() {
      //AXE_LIST_DELETE_ELEMENTS(file_list, axfs_file *);
    }
};
#endif // __AXFS_STATE_H__

/* $Id: axfs_state.h,v 1.2 2004/06/09 18:23:55 doneval Exp $ */
