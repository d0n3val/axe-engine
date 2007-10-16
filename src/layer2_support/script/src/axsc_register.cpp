/**
* @file
* Add functions, vars, objects, methods, properties, etc ...
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      27 May 2004
*/
#include "axsc_stdafx.h"

/**
* Add a global var access to the script
*/
AXSC_API int axsc_register_variable( const char* declaration, void* address )
{
  // check params
  AXE_ASSERT( NULL != declaration && NULL != address );

  // check current state
  AXE_ASSERT( NULL != state.engine );
  AXE_ASSERT( AXSC_EXEC_STATE_INIT == state.execution_state );

  int res = state.engine->RegisterGlobalProperty( declaration, address );
  check_return_value( res );

  return( AXE_TRUE );
}

/**
* Add a global function to the script
*/
AXSC_API int axsc_register_function( const char* declaration, asUPtr function )
{
  // check params
  AXE_ASSERT( NULL != declaration );

  // check current state
  AXE_ASSERT( NULL != state.engine );
  AXE_ASSERT( AXSC_EXEC_STATE_INIT == state.execution_state );

  int res = state.engine->RegisterGlobalFunction( declaration, function, asCALL_CDECL );
  check_return_value( res );

  return( AXE_TRUE );
}

/**
* Registers the main string factory
*/
AXSC_API int axsc_register_string_factory( const char* data_type, asUPtr function )
{
  // check params
  AXE_ASSERT( NULL != data_type );

  // check current state
  AXE_ASSERT( NULL != state.engine );
  AXE_ASSERT( AXSC_EXEC_STATE_INIT == state.execution_state );

  int res = state.engine->RegisterStringFactory( data_type, function, asCALL_CDECL );
  check_return_value( res );

  return( AXE_TRUE );
}

/* $Id: axsc_register.cpp,v 1.3 2004/09/20 21:28:13 doneval Exp $ */
