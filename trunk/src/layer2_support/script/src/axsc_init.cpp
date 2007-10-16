/**
* @file
* Init and deinit functions
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      27 May 2004
*/
#include "axsc_stdafx.h"

/**
* Init script engine
*/
AXSC_API int axsc_init() {

  // check current state
  AXE_ASSERT( AXSC_EXEC_STATE_DONE == state.execution_state );
  AXE_ASSERT( NULL == state.engine );

  // Check angelscript version
  AXE_ASSERT( 10902 == ANGELSCRIPT_VERSION );

  state.engine = asCreateScriptEngine( ANGELSCRIPT_VERSION );
  AXE_ASSERT( NULL != state.engine );
  state.execution_state = AXSC_EXEC_STATE_INIT;

  return( AXE_TRUE );
}

/**
* Close script engine
*/
AXSC_API int axsc_done() {

  if ( NULL != state.engine ) {
    state.engine->Release();
    state.engine = NULL;
    if ( NULL != state.context ) {
      state.context->Release();
      state.context = NULL;
    }
  }

  state.execution_state = AXSC_EXEC_STATE_DONE;

  return( AXE_TRUE );
}

/* $Id: axsc_init.cpp,v 1.3 2004/09/26 21:55:58 doneval Exp $ */
