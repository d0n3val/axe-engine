/**
* @file
* Pre-compiled header
*/

/*$1- Other compiling options ------------------------------------------------*/
#pragma once

/*$1- Common includes --------------------------------------------------------*/
#include "axe_internal_defs.h"
#include "axe_defs.h"

/*$1- Python headers and libs ------------------------------------------------*/
#include "Python25/include/Python.h"
#ifdef _DEBUG
  #pragma comment( lib, "src/Python25/libs/python25.lib" )
  #pragma message( "WARNING: Avoid compiling axe_python in debug, use release version instead !!!" )
#else
  #pragma comment( lib, "src/Python25/libs/python25.lib" )
#endif

/*$1- Other AXE libs needed --------------------------------------------------*/
#include "axe_any.h"
#include "axe_string.h"

/*$1- User includes ----------------------------------------------------------*/
#include "axe_python.h"

/*$1- State ------------------------------------------------------------------*/
#include "axe_state.h"
#include "axpy_state.h"

extern axpy_state state;

/* $Id: axpy_stdafx.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
