/**
* @file
* Axe 'windows' library PRIVATE include header
*/
#ifndef __AXWD_WINDOWS_H__
  #define __AXWD_WINDOWS_H__

LRESULT CALLBACK  wndproc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

// axwd_windows.cpp ----------------------------------------------------------
int               display_output( const int, const char* , const char*  );

int               change_resolution( int width, int height, int fullscreen );
int               update_window_rectangle();
void              get_current_resolution( int& width, int& height );
void              call_resize_callback();
LRESULT CALLBACK  window_creation_hook( int hook_code, WPARAM wParam, LPARAM lParam );
#endif /*__AXWD_WINDOWS_H__*/

/* $Id: axwd_windows.h,v 1.1 2004/06/09 18:23:59 doneval Exp $ */
