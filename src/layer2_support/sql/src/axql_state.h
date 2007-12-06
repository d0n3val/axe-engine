/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXQL_STATE_H__
  #define __AXQL_STATE_H__

  #include "axql_stdafx.h"

  #define MAX_DIR_LEN 256

/**
* This class stores all data related to the state of the library
*/
class axql_state : public axe_state
{
  public:
    char                default_directory[MAX_DIR_LEN];
    sqlite3*            database;
    AXQL_QUERY_CALLBACK query_callback;
    void*               userdata;
  public:
    axql_state() :
    axe_state()
    {
      lib_id = 'AXQL';
      strcpy_s( lib_name, LIB_NAME_LONG, "Sql" );
      lib_version = 1;

      strcpy_s( default_directory, MAX_DIR_LEN, ".\\" );

      // -----------------------------------------------
      database = NULL;
      query_callback = NULL;
      userdata = NULL;
    }

    ~axql_state()
    {
      if( database != NULL )
      {
        axql_close_db();
      }
    }
};
#endif // __AXQL_STATE_H__

/* $Id: axrt_state.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
