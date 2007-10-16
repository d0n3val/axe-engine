/**
* @file
* Compiles the script
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      29 May 2004
*/
#include "axsc_stdafx.h"

// This is a simple output stream class
class COutStream : public asIOutputStream
{
  public:

    COutStream::COutStream() {
      state.compile_report.clear();
    }

    void Write( const char* text )
    {
      state.compile_report += text;
    }
};

/**
* Compile loaded scripts
*/
AXSC_API int axsc_compile()
{
  // check current state
  AXE_ASSERT( AXSC_EXEC_STATE_LOADED == state.execution_state );

  // to store the result
  COutStream  out;

  int         res = state.engine->Build( AXSC_MODULE_NAME, &out );
  AXE_ASSERT_MSG( res >= 0, state.compile_report );

  // create the context
  res = state.engine->CreateContext( &state.context );
  check_return_value(res);

  state.execution_state = AXSC_EXEC_STATE_COMPILED;

  return( AXE_TRUE );
}

/* $Id: axsc_compile.cpp,v 1.3 2004/09/20 21:28:13 doneval Exp $ */
