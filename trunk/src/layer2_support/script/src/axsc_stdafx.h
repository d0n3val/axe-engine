/**
* @file
* Pre-compiled header
*/

/*$1- Other compiling options ------------------------------------------------*/
#pragma once

/*$1- Common includes --------------------------------------------------------*/
#include "axe_internal_defs.h"
#include "axe_defs.h"

/*$1- Other AXE libs needed --------------------------------------------------*/
#include "axe_list.h"
#include "axe_string.h"
#include "axe_file_system.h"

/*$1- AngelScript code -------------------------------------------------------*/
#include "angelscript/angelscript.h"
#ifdef _DEBUG
  #pragma comment( lib, "src/angelscript/angelscript_d.lib" )
#else
  #pragma comment( lib, "src/angelscript/angelscript.lib" )
#endif

/*$1- User defines -----------------------------------------------------------*/
#define AXSC_MODULE_NAME  "axe"

/*$1- User includes ----------------------------------------------------------*/
#include "axe_script.h"
#include "axsc_script.h"

/*$1- State ------------------------------------------------------------------*/
#include "axe_state.h"
#include "axsc_state.h"

extern axsc_state state;

/* $Id: axsc_stdafx.h,v 1.4 2004/09/10 23:06:47 doneval Exp $ */
