
 /**
* @file
* High level init / finalize functions
*/
#include "axpy_stdafx.h"

/**
* Starts Python VM
*/
AXPY_API int axpy_init ()
{
  Py_Initialize();
  return( AXE_TRUE );
}

/**
* Stops Python VM
*/
AXPY_API int axpy_finalize()
{
  Py_Finalize();
  return( AXE_TRUE );
}

/* $Id: axpy_python.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
