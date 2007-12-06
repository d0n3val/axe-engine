/**
* @file
* Axe 'Sql' library PUBLIC include header (interface to SQLite lib)
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  06 Dec 2007 
*/
#ifndef __AXE_SQL_H__
  #define __AXE_SQL_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1-  DLL proper function prefix --------------------------------------------*/
  #ifdef _USRDLL
    #define AXQL_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Sql' library ..." )
  #else
    #define AXQL_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Sql' library ..." )

/*$1-  Automatic .lib link ---------------------------------------------------*/
    #ifndef AXQL_NO_AUTOLINK
      #pragma comment( lib, "axe_sql.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axql_states
{
  AXQL_VERSION      = 1,
  AXQL_LIBRARY_NAME,
  AXQL_LIBRARY_ID,
  AXQL_DEBUG_MODE,
  AXQL_LAST_ERROR,
  AXQL_STATE_COUNT,
};

typedef int ( *AXQL_QUERY_CALLBACK ) (void*userdata, int argc, char**argv, char**azColName);

/** @example axql_test.cpp */
extern "C"
{

  /*$1- axql_sql.cpp ---------------------------------------------------------*/
  AXQL_API unsigned int axql_get( const int query_state );
  AXQL_API unsigned int axql_set( const int query_state, const unsigned int new_value );
  AXQL_API const char*  axql_get_error_message( const unsigned int error_number );
  AXQL_API int          axql_set_error_callback( void (*error_callback) (int, const char*, long) );

  AXQL_API int          axql_get_int( const int query_state );
  AXQL_API int          axql_set_int( const int query_state, const int new_value );

  /*$1- axql_db.cpp ----------------------------------------------------------*/
  AXQL_API int  axql_open_db( const char* file_name );
  AXQL_API int  axql_close_db();
  AXQL_API int  axql_set_query_callback( AXQL_QUERY_CALLBACK callback, void* userdata );
  AXQL_API int  axql_query( const char* query );
} // extern "C"
#endif // __AXE_SQL_H__

/* $Id: axe_sql.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
