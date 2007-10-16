/**
* @file
* Functions to be able to call script functions
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      30 May 2004
*/
#include "axsc_stdafx.h"

#define MAX_SCRIPT_FUNCTION_LEN 256

/**
* Helper function
*/
int bytes_to_dword( size_t bytes )
{
  if( bytes % 4 > 0 )
  {
    return( (int) ((bytes / 4) + 1) );
  }
  else
  {
    return( (int) (bytes / 4) );
  }
}

/**
* Begin call function block
*/
AXSC_API int axsc_begin_call_function( const char* function_name )
{
  // check arguments
  AXE_ASSERT( NULL != function_name );

  // check current execution state
  AXE_ASSERT( AXSC_EXEC_STATE_COMPILED == state.execution_state );

  int function_id = state.engine->GetFunctionIDByName( AXSC_MODULE_NAME, function_name );
  AXE_ASSERT( function_id >= 0 );

  // Prepare the context
  int res = state.context->Prepare( state.engine->GetFunctionIDByName(AXSC_MODULE_NAME, function_name) );
  check_return_value(res);

  state.execution_state = AXSC_EXEC_STATE_EXECUTING;
  state.current_argument = 0;
  return( AXE_TRUE );
}

/**
* Add argument to the function call block
*/
AXSC_API int axsc_add_argument( void* argument, size_t sizeof_argument )
{
  // check arguments
  AXE_ASSERT( NULL != argument && sizeof_argument > 0 );

  // check current execution state
  AXE_ASSERT( AXSC_EXEC_STATE_EXECUTING == state.execution_state );

  int dword_size = bytes_to_dword( sizeof_argument );
  int res = state.context->SetArguments( state.current_argument, (asDWORD*) argument, dword_size );

  // If this assert fails, it's possible that this function does not accept more arguments
  check_return_value(res);

  ++state.current_argument;

  return( AXE_TRUE );
}

/**
* Set the return value of the function call block
*/
AXSC_API int axsc_set_return_value( void* return_value, size_t sizeof_return_value )
{
  // check arguments
  AXE_ASSERT( NULL != return_value && sizeof_return_value > 0 );

  // check current execution state
  AXE_ASSERT( AXSC_EXEC_STATE_EXECUTING == state.execution_state );

  state.return_value = return_value;
  state.return_value_size = bytes_to_dword( sizeof_return_value );
  return( AXE_TRUE );
}

/**
* End the function call block and execute it!
*/
AXSC_API axsc_execution axsc_end_call_function()
{
  // check current execution state
  AXE_ASSERT( AXSC_EXEC_STATE_EXECUTING == state.execution_state );

  axsc_execution  execution_result;
  int             res;

  execution_result = AXSC_EXECUTION_ERROR;
  res = state.context->Execute();
  check_return_value(res);

  switch( res )
  {
    case asEXECUTION_FINISHED:
      {
        if( NULL != state.return_value && state.return_value_size > 0 )
        {
          // fill return value with data
          state.context->GetReturnValue( (asDWORD*) state.return_value, state.return_value_size );

          // clear vars
          state.return_value = NULL;
          state.return_value_size = 0;

          execution_result = AXSC_EXECUTION_FINISHED;
        }
      }

      break;

    case asEXECUTION_SUSPENDED:
      {
        execution_result = AXSC_EXECUTION_SUSPENDED;

        char  function_name[MAX_SCRIPT_FUNCTION_LEN];
        int   function_id = state.context->GetCurrentFunction();
        res = state.engine->GetFunctionName( function_id, (char*) function_name, MAX_SCRIPT_FUNCTION_LEN );
        check_return_value(res);

        //printf( "func : %s\n", function_name );
        //printf( "line : %d\n", state.context->GetCurrentLineNumber() );
      }

      break;
  }

  state.execution_state = AXSC_EXEC_STATE_COMPILED;

  return( execution_result );
}

/* $Id: axsc_call_function.cpp,v 1.4 2004/09/20 21:28:13 doneval Exp $ */
