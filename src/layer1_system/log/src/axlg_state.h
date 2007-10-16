/**
* @file
* _state class include header
* Used to store all data about current library state
*/
#ifndef __AXLG_STATE_H__
  #define __AXLG_STATE_H__

  #include "axlg_stdafx.h"

/**
* This class stores all data related to the state of the library
*/
class axlg_state : public axe_state
{
  public:
    axe_list<axe_string>  string_list;

    // filters
    axe_string            filter;
    axlg_priority         min_priority;

    // next log reference
    int                   ref_exist;
    int                   ref_valid;
    char                  ref_file[1024];
    unsigned long         ref_line;
    axlg_priority         ref_priority;

    // list of possible outputs (future: sockets, file, HTML, email, etc...)
    int                   output_to_console;
  public:
    axlg_state() :
    axe_state() {
      lib_id = 'AXLG';
      strcpy_s( lib_name, LIB_NAME_LONG, "Log" );
      lib_version = 1;

      // set initial filters
      filter.clear();
      min_priority = AXLG_INFO;

      // disable initial ref
      ref_exist = AXE_FALSE;
      ref_valid = AXE_TRUE;
      ref_line = 0;
      ref_file[0] = 0;
      ref_priority = AXLG_INFO;

      // default log output
      output_to_console = AXE_TRUE;
    }

    ~axlg_state() {
    }
};
#endif // __AXLG_STATE_H__

/* $Id: axlg_state.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
