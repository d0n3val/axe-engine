/**
* @file
* Global definitions to use in the internals of each lib
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @version   1.0
* @date      11 Apr 2004
*/
#ifndef __AXE_INTERNAL_DEFS_H__
  #define __AXE_INTERNAL_DEFS_H__

// ****************************************************************************
// *********************** CHECK ENVIROMENT SAFETY ****************************
// ****************************************************************************

/*$1- Process this.h only once -----------------------------------------------*/
  #pragma once

/*$1- Do not use stupid win32 stuff ------------------------------------------*/
  #define WIN32_LEAN_AND_MEAN

/*$1- Check compiler version -------------------------------------------------*/
  #ifndef _MSC_VER
    #error "This code will only compile in MS Visual Studio"
  #endif
  #if _MSC_VER < 1300
    #error "This code will only compile in MS Visual Studio"
  #endif

/*$1- We can work only with WIN32 right now ----------------------------------*/
  #ifndef _WIN32
    #error "This code only works under WIN32"
  #endif

/*$1- Look por C++ -----------------------------------------------------------*/
  #ifndef __cplusplus
    #error "This code need a C++ compiler"
  #endif

/*$1- We do not allow exceptions ---------------------------------------------*/
//  #ifdef _CPPUNWIND
//    #error "You must disable exceptions"
  //#endif

/*$1- We also do not allow RTTI ----------------------------------------------*/
  #ifdef _CPPRTTI
    #error "You must disable RTTI"
  #endif

/*$1- Look for Pentium -------------------------------------------------------*/
  #ifndef _M_IX86
    #error "This code is for X86"
  #endif
  #if _M_IX86 < 500
    #error "You need Pentium or better to compile"
  #endif

/*$1- Seems to be safe to put this here --------------------------------------*/
  #include <windows.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <crtdbg.h>
  #include <assert.h>
  #include "axe_errors.h"

#define _CRT_SECURE_NO_WARNINGS
  
#endif // __AXE_INTERNAL_DEFS_H__

/* $Id: axe_internal_defs.h,v 1.3 2004/07/27 21:19:26 ilgenio Exp $ */
