/**
* @file
* High level init / finalize functions
*/
#include "axpy_stdafx.h"

/**
* Starts Python VM
*/
AXPY_API int axpy_init()
{
  AXE_ASSERT( state.init == false );

  Py_Initialize();
  state.init = true;

  return( AXE_TRUE );
}

/**
* Stops Python VM
*/
AXPY_API int axpy_finalize()
{
  AXE_ASSERT( state.init == true );

  Py_Finalize();
  state.init = false;

  return( AXE_TRUE );
}

/* $Id: axpy_python.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
