  /*  *
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXSC_STATE_H__
  #define __AXSC_STATE_H__

  #include "axsc_stdafx.h"

enum axsc_execution_state
{
  AXSC_EXEC_STATE_DONE       = 0,
  AXSC_EXEC_STATE_INIT,
  AXSC_EXEC_STATE_LOADED,
  AXSC_EXEC_STATE_COMPILED,
  AXSC_EXEC_STATE_EXECUTING
};

#define AXSC_MAX_CLASS_NAME 256

/**
* This class stores all data related to the state of the library
*/
class axsc_state : public axe_state
{
  public:
    asIScriptEngine*      engine;
    asIScriptContext*     context;
    axsc_execution_state  execution_state;
    axe_string            current_registering_class;
    axe_string            compile_report;
    int                   current_argument;
    void*                 return_value;
    int                   return_value_size;
  public:
    axsc_state() :
    axe_state() {
      lib_id = 'AXSC';
      strcpy_s( lib_name, LIB_NAME_LONG, "Script" );
      lib_version = 1;

      engine = NULL;
      context = NULL;
      execution_state = AXSC_EXEC_STATE_DONE;
      current_argument = 0;
      return_value = NULL;
      return_value_size = 0;
    }

    ~axsc_state() {
      axsc_done();
    }
};
#endif // __AXSC_STATE_H__

/* $Id: axsc_state.h,v 1.1 2004/06/09 18:24:09 doneval Exp $ */
