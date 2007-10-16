/**
* @file
* Pre-compiled header
*/

/*$1- Other compiling options ------------------------------------------------*/
#pragma once

/*$1- Common includes --------------------------------------------------------*/
#include "axe_internal_defs.h"
#include "axe_defs.h"

/*$1- OpenGL libs required ---------------------------------------------------*/
#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

/*$1- OpenGL includes --------------------------------------------------------*/
#include <GL/gl.h>
#include <GL/glu.h>

/*$1- Other AXE libs needed --------------------------------------------------*/
#include "axe_string.h"

/*$1- User includes ----------------------------------------------------------*/
#include "axe_raster.h"

/*$1- State ------------------------------------------------------------------*/
#include "axe_state.h"
#include "axrt_state.h"
#include "axrt_raster.h"

extern axrt_state state;

/* $Id: axrt_stdafx.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
