/**
* @file
* Run scripts from strings / files
*/
#include "axpy_stdafx.h"

/**
* Runs a buffer as Python code
*/
AXPY_API int axpy_exec( const char* code )
{
  AXE_ASSERT( state.init == true );
  AXE_ASSERT( code != NULL );

  PyRun_SimpleString( code );
  return( AXE_TRUE );
}

#ifdef _DEBUG
  #define Py_DECREF(a) __noop
#define Py_XDECREF(a) __noop
#endif

/**
* Opens a file and runs Python code in it
*/
AXPY_API int axpy_load_file( const char* file_name, const char* function_name )
{
  AXE_ASSERT( state.init == true );
  AXE_ASSERT( file_name != NULL );
  AXE_ASSERT( function_name != NULL );

  PyObject*   file = PyString_FromString( file_name );
  PyObject*   module = PyImport_Import( file );
  Py_DECREF( file );

  if( module == NULL )
  {
    return( AXE_FALSE );
  }

  PyObject*   function = PyObject_GetAttrString( module, function_name );

  if( function != NULL && PyCallable_Check(function) )
  {
    PyObject*   result = PyObject_CallObject( function, NULL );

    if( result == NULL )
    {
      Py_DECREF( function );
      Py_DECREF( module );
      return( AXE_FALSE );
    }
    else
    {
      Py_DECREF( result );
    }
  }
  else
  {
    Py_DECREF( module );
    return( AXE_FALSE );
  }

  Py_XDECREF( function );
  Py_DECREF( module );

  return( AXE_TRUE );
}

/* $Id: axpy_python.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
