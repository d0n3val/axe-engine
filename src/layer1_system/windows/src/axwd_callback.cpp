/**
* @file
* Help functions to clarify this horrible windows code :(
*/
#include "axwd_stdafx.h"

/**
* Changes resolution and screen mode to fullscreen
*/
AXWD_API int axwd_on_main_loop( int (*func) () ) {
  //AXE_CHECK_DBG_ERROR( (NULL != func), AXE_ERROR_MSG_BAD_ARGUMENTS );
  state.on_loop = func;
  return( AXE_TRUE );
}

/**
* Changes resolution and screen mode to fullscreen
*/
AXWD_API int axwd_on_start( int (*func) () ) {
  state.on_start = func;
  return( AXE_TRUE );
}

/**
* Changes resolution and screen mode to fullscreen
*/
AXWD_API int axwd_on_end( int (*func) () ) {
  state.on_end = func;
  return( AXE_TRUE );
}

/**
* Changes resolution and screen mode to fullscreen
*/
AXWD_API int axwd_on_resize( int (*func) (int, int, int, int, int) ) {
  state.on_resize = func;
  return( AXE_TRUE );
}

/**
* Changes resolution and screen mode to fullscreen
*/
AXWD_API int axwd_on_focus( int (*func) (int) ) {
  state.on_focus = func;
  return( AXE_TRUE );
}

/* $Id: axwd_callback.cpp,v 1.2 2004/09/20 21:28:11 doneval Exp $ */
