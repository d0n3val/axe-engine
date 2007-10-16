/**
* @file
* Manages events for the game window
*/
#include "axwd_stdafx.h"

/**
* Change display to fullscreen
*/
AXWD_API int axwd_change_to_fullscreen()
{
  if( state.fullscreen == AXE_TRUE )
  {
    return( AXE_TRUE );
  }

  if( state.started == AXE_FALSE )
  {
    state.fullscreen = AXE_TRUE;
    return( AXE_TRUE );
  }

  // within this operation we must ignore resize orders
  state.ignore_resize = AXE_TRUE;
  state.set_pause( true );

  // Change window style
  LONG  result = SetWindowLong( state.window, GWL_STYLE, state.fullscreen_style );

  if( result == 0 )
  {
    state.ignore_resize = AXE_FALSE;
  }

  AXE_CHECK_ERROR( (0 == result), 18 );

  // Make sure of window size/position
  BOOL  res = SetWindowPos(
      state.window,
      HWND_NOTOPMOST,
      0,
      0,
      state.fullscreen_resolution_width,
      state.fullscreen_resolution_height,
      SWP_SHOWWINDOW | SWP_FRAMECHANGED );

  if( FALSE != res )
  {
    state.ignore_resize = AXE_FALSE;
  }

  AXE_CHECK_ERROR( (FALSE != res), 17 );

  // update state and call user defined callback
  update_window_rectangle();
  state.fullscreen = AXE_TRUE;
  state.ignore_resize = AXE_FALSE;
  state.set_pause( false );

  call_resize_callback();

  // change resolution if needed
  /*if(change_resolution(state.fullscreen_resolution_width, 
	state.fullscreen_resolution_height, AXE_TRUE) != AXE_TRUE) {
	return(AXE_FALSE);
	}*/
  return( AXE_TRUE );
}

/**
* Change display to windowed
*/
AXWD_API int axwd_change_to_windowed()
{
  if( state.fullscreen == AXE_FALSE )
  {
    return( AXE_TRUE );
  }

  if( state.started == AXE_FALSE )
  {
    state.fullscreen = AXE_FALSE;
    return( AXE_TRUE );
  }

  // within this operation we must ignore resize orders
  state.ignore_resize = AXE_TRUE;
  state.set_pause( true );

  // Change window style
  int result = SetWindowLongPtr( state.window, GWL_STYLE, state.windowed_style );
  if( 0 == result )
  {
    state.ignore_resize = AXE_FALSE;
  }

  AXE_CHECK_ERROR( (0 == result), 18 );

  // Make sure of window size/position
  BOOL  res = SetWindowPos(
      state.window,
      HWND_NOTOPMOST,
      100,
      100,
      state.windowed_resolution_width - 100,
      state.windowed_resolution_height - 100,
      SWP_SHOWWINDOW | SWP_FRAMECHANGED );
  if( FALSE == res )
  {
    state.ignore_resize = AXE_FALSE;
  }

  AXE_CHECK_ERROR( (FALSE == res), 17 );

  // update state
  state.fullscreen = AXE_FALSE;
  update_window_rectangle();
  state.ignore_resize = AXE_FALSE;
  state.set_pause( false );

  call_resize_callback();

  // change resolution if needed
  /* this causes ded_device->Present() to fail
	if(change_resolution(state.windowed_resolution_width, 
		state.windowed_resolution_height, AXE_FALSE) != AXE_TRUE) {
		return(AXE_FALSE);
	}*/
  return( AXE_TRUE );
}

/**
* Comment
*/
AXWD_API int axwd_toggle_fullscreen()
{
  if( state.fullscreen == AXE_TRUE )
  {
    axwd_change_to_windowed();
  }
  else
  {
    axwd_change_to_fullscreen();
  }

  return( AXE_TRUE );
}

/**
* Comment
*/
AXWD_API win_info axwd_get_windows_info()
{
  win_info  info;

  info.device_context = state.device_context;
  info.instance = state.instance;
  info.window = state.window;
  info.window_style = state.window_style;

  return( info );
}

/**
* Comment
*/
AXWD_API screen_info axwd_get_screen_info()
{
  screen_info info;

  update_window_rectangle();

  info.top = state.client_rectangle.top;
  info.bottom = state.client_rectangle.bottom;
  info.right = state.client_rectangle.right;
  info.left = state.client_rectangle.left;

  info.window_width = info.right - info.left;
  info.window_height = info.bottom - info.top;

  info.aspect_ratio = (float) info.window_width / (float) info.window_height;

  if( state.fullscreen == AXE_FALSE )
  {
    info.screen_width = state.windowed_resolution_width;
    info.screen_height = state.windowed_resolution_height;
  }
  else
  {
    info.screen_width = state.fullscreen_resolution_width;
    info.screen_height = state.fullscreen_resolution_height;
  }

  return( info );
}

/**
* Comment
*/
AXWD_API int axwd_show_cursor( int show_cursor )
{
  if( show_cursor == 0 )
  {
    state.hide_mouse = AXE_FALSE;
    if( state.mouse_in_window == AXE_TRUE )
    {
      ShowCursor( FALSE );
    }
  }
  else
  {
    state.hide_mouse = AXE_TRUE;
    ShowCursor( TRUE );
  }

  return( AXE_TRUE );
}

/**
* Comment
*/
AXWD_API int axwd_set_cursor( const char* cursor_file )
{
  if( cursor_file == NULL )
  {
    return( AXE_FALSE );
  }

  strcpy_s( state.cursor_file, 255, cursor_file );
  return( AXE_TRUE );
}

/**
* Comment
*/
AXWD_API int axwd_set_icon( const char* icon_file )
{
  if( icon_file == NULL )
  {
    return( AXE_FALSE );
  }

  strcpy_s( state.ico_file, 255, icon_file );
  return( AXE_TRUE );
}

/**
* Comment
*/
AXWD_API int axwd_set_small_icon( const char* small_icon_file )
{
  if( small_icon_file == NULL )
  {
    return( AXE_FALSE );
  }

  strcpy_s( state.small_ico_file, 255, small_icon_file );
  return( AXE_TRUE );
}

/**
* Comment
*/
AXWD_API int axwd_set_application_name( const char* application_name )
{
  if( application_name == NULL )
  {
    return( AXE_FALSE );
  }

  strcpy_s( state.application_name, 255, application_name );
  return( AXE_TRUE );
}

/**
* Comment
*/
AXWD_API int axwd_set_window_title( const char* window_title )
{
  if( window_title == NULL )
  {
    return( AXE_FALSE );
  }

  strcpy_s( state.window_name, 255, window_title );
  return( AXE_TRUE );
}

/* $Id: axwd_utils.cpp,v 1.1 2004/06/09 18:23:59 doneval Exp $ */
