/**
* @file
* Help functions to clarify this horrible windows code :(
*/
#include "axwd_stdafx.h"

/**
* Changes resolution and screen mode
*/
int change_resolution( int width, int height, int fullscreen ) {

  // Create the device mode var and clear it
  DEVMODE dmode;

  // Get current settings
  BOOL result = EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmode);
  AXE_CHECK_DBG_ERROR((FALSE != result), 15);

  // set width and height
  dmode.dmPelsWidth = width;
  dmode.dmPelsHeight = height;

  // change to screen mode
  int res;
  if( fullscreen == AXE_TRUE ) {
    res = ChangeDisplaySettings( &dmode, CDS_FULLSCREEN );
  } else {
    res = ChangeDisplaySettings( &dmode, 0 );
  }

  // check
  AXE_CHECK_DBG_ERROR((DISP_CHANGE_SUCCESSFUL != result), 16);

  // all ok ;^)
  return( AXE_TRUE );
}

/**
* Reads the window rect and saves it
*/
int update_window_rectangle() {
  GetWindowRect( state.window, &state.window_rectangle );
  GetClientRect( state.window, &state.client_rectangle );
  return( AXE_TRUE );
}

/**
* Reads the window rect and saves it
*/
void get_current_resolution( int& width, int& height ) {
  HDC desktop_dc = GetDC( GetDesktopWindow() );

  width = GetDeviceCaps( desktop_dc, HORZRES );
  height = GetDeviceCaps( desktop_dc, VERTRES );
}

/**
* Reads the window rect and saves it
*/
void call_resize_callback() {
  if( state.on_resize != NULL && state.ignore_resize == AXE_FALSE ) {
    state.on_resize(
        state.client_rectangle.left,
        state.client_rectangle.top,
        state.client_rectangle.right,
        state.client_rectangle.bottom,
        state.fullscreen );
  }
}

/* $Id: axwd_misc.cpp,v 1.1 2004/06/09 18:23:59 doneval Exp $ */
