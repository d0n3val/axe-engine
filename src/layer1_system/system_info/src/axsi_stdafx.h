/**
* @file
* Pre-compiled header
*/
// ---------------------------
#ifndef WIN32
  #error "This code only works under WIN32"
#endif
#ifndef __cplusplus
  #error "This code need a C++ WIN32 compiler"
#endif

// ---------------------------
#pragma once

// ---------------------------
#define WIN32_LEAN_AND_MEAN
#define AXE_SYSTEM_INFO_DLL

// ---------------------------
// Erase this if you don't need the memory manager
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

// ---------------------------
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <crtdbg.h>

// ---------------------------
#include "axe_system_info.h"
#include "axsi_system_info.h"
#include "axsi_state.h"
#include "axsi_timer.h"
#include "axsi_system.h"
#include "axsi_cpu_flags.h"
#include "axsi_display.h"
#include "axsi_errors.h"

/* $Id: axsi_stdafx.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
