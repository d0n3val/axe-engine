/**
* @file
* Load script file and call preprocessor
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      28 May 2004
*/
#include "axsc_stdafx.h"

/**
* Loads an script file and parse it with the preprocessor
*/
AXSC_API int axsc_load_file( const char* file_name )
{
  // check arguments
  AXE_ASSERT( NULL != file_name );

  // check current state
  AXE_ASSERT( AXSC_EXEC_STATE_INIT == state.execution_state );

  AXE_ID  file_id;

  file_id = axfs_create( file_name, AXE_FALSE );

  int res = state.engine->AddScriptSection(
      AXSC_MODULE_NAME,
      file_name,
      (const char*) axfs_get_data(file_id, AXE_FALSE),
      (int) axfs_get_size(file_id),
      0 );

  check_return_value(res);

  axfs_destroy( file_id, AXE_FALSE );

  state.execution_state = AXSC_EXEC_STATE_LOADED;

  return( AXE_TRUE );
}

/* $Id: axsc_load_file.cpp,v 1.3 2004/09/20 21:28:13 doneval Exp $ */
