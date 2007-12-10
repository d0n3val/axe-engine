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

  axe_any a(3);
  axe_any b(3.0);
  axe_any c(3.0f);
  axe_any d(&("hola mundo"));
  axe_any e(false);

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
