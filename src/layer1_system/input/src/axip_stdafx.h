/**
* @file
* Pre-compiled header
*/

/*$1- Other compiling options ------------------------------------------------*/
#pragma once

/*$1- Common includes --------------------------------------------------------*/
#include "axe_internal_defs.h"
#include "axe_defs.h"

/*$1- MS DirectInput ---------------------------------------------------------*/
#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

/*$1- Max events stored between calls to update ------------------------------*/
#define MAX_KEYBOARD_EVENTS 64
#define MAX_MOUSE_EVENTS    128

/*$1- Other AXE libs needed --------------------------------------------------*/
#include "axe_log.h"
#include "axe_list.h"
#include "axe_dyn_array.h"

/*$1- User includes ----------------------------------------------------------*/
#include "axe_input.h"
#include "axip_device.h"
#include "axip_keyboard.h"
#include "axip_mouse.h"
#include "axip_input.h"

/*$1- State ------------------------------------------------------------------*/
#include "axe_state.h"
#include "axip_state.h"

extern axip_state state;

/* $Id: axip_stdafx.h,v 1.3 2004/09/20 21:28:09 doneval Exp $ */
