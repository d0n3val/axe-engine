/**
* @file
* Open, Close and execute SQL query
*/
#include "axql_stdafx.h"

/**
* Open database file or memory database
*/
AXQL_API int axql_open_db( const char* file_name )
{
  AXE_ASSERT( state.database == NULL );

  int res = -1;

  if( file_name == NULL )
  {
    res = sqlite3_open( ":memory:", &state.database );
  }
  else
  {
    res = sqlite3_open( file_name, &state.database );
  }

  if( res != SQLITE_OK )
  {
    AXE_SET_ERROR( 10 );
    axql_close_db();
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/**
* Closes current database
*/
AXQL_API int axql_close_db( void )
{
  AXE_ASSERT( state.database != NULL );

  if( state.database != NULL )
  {
    sqlite3_close( state.database );
    state.database = NULL;
    return( AXE_TRUE );
  }

  return( AXE_FALSE );
}

/**
* Sets the callback to be used when dumping query results
*/
AXQL_API int axql_set_query_callback( AXQL_QUERY_CALLBACK callback, void* userdata )
{
  AXE_ASSERT( callback != NULL );

  state.query_callback = callback;
  state.userdata = userdata;
  return( AXE_TRUE );
}

/**
* Executes a query
*/
AXQL_API int axql_query( const char* query )
{
  AXE_ASSERT( state.database != NULL );
  AXE_ASSERT( query != NULL );

  int res = sqlite3_exec( state.database, query, state.query_callback, state.userdata, NULL );

  if( res != SQLITE_OK )
  {
    AXE_SET_ERROR( 10 );
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/* $Id: axrt_raster.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
