/**
* @file
* _state class include header
* Used to store all data about current library state
*/
#ifndef __AXWD_STATE_H__
  #define __AXWD_STATE_H__

  #include "axwd_stdafx.h"

/**
* This class stores all data related to the state of the library
*/
class axwd_state : public axe_state
{
  public:
    HINSTANCE instance;
    HWND      window;
    DWORD     window_style;
    DWORD     window_style_ex;
    LONG_PTR  fullscreen_style;
    LONG_PTR  windowed_style;
    DWORD     fullscreen_style_ex;
    DWORD     windowed_style_ex;
    RECT      window_rectangle;
    RECT      client_rectangle;
    HDC       device_context;
    HHOOK     window_creation_hook;
    int       windowed_resolution_width;
    int       windowed_resolution_height;
    int       fullscreen_resolution_width;
    int       fullscreen_resolution_height;
    int       color_depth;

    char      application_name[255];
    char      window_name[255];

    // icons
    char      ico_file[255];
    char      small_ico_file[255];
    char      cursor_file[255];

    // flags
    int       fullscreen;
    int       maximized;
    int       minimized;
    int       exiting;
    int       started;
    int       paused;
    int       pause_count;
    int       device_lost;
    int       mouse_in_window;
    int       hide_mouse;
    int       ignore_resize;

    // callbacks
    int ( *on_loop ) ();
    int ( *on_start ) ();
    int ( *on_end ) ();
    int ( *on_resize ) (int, int, int, int, int);
    int ( *on_focus ) (int);
    int ( *on_suspend ) ();
    int ( *on_resume_suspend ) ();
    int ( *on_repaint ) ();
    int ( *on_key ) (char);
    int ( *on_mouse_in_window ) (int, int, int);
    int ( *on_pause ) ();
    int ( *on_resume ) ();
  public:
    axwd_state() :
    axe_state() {
      lib_id = 'AXWD';
      strcpy_s( lib_name, LIB_NAME_LONG, "Windows" );
      lib_version = 1;

      instance = 0;
      window = 0;
      device_context = 0;
      fullscreen_style = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
      fullscreen_style_ex = 0;

      windowed_style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
      windowed_style_ex = WS_EX_OVERLAPPEDWINDOW;

      window_creation_hook = NULL;

      strcpy_s( application_name, 255, "Application Name" );
      strcpy_s( window_name, 255, "Window Name" );

      ico_file[0] = small_ico_file[0] = cursor_file[0] = 0;

      windowed_resolution_width = windowed_resolution_height = 0;
      fullscreen_resolution_width = fullscreen_resolution_height = 0;

      window_rectangle.right = window_rectangle.left = 0;
      window_rectangle.top = window_rectangle.bottom = 0;

      client_rectangle.right = client_rectangle.left = 0;
      client_rectangle.top = client_rectangle.bottom = 0;

      color_depth = 24;

      fullscreen = AXE_TRUE;
      exiting = AXE_FALSE;
      device_lost = AXE_FALSE;
      started = AXE_FALSE;
      paused = AXE_FALSE;
      pause_count = 0;
      mouse_in_window = AXE_TRUE;
      hide_mouse = AXE_TRUE;
      ignore_resize = AXE_FALSE;

      on_loop = NULL;
      on_start = NULL;
      on_end = NULL;
      on_resize = NULL;
      on_focus = NULL;
      on_suspend = NULL;
      on_resume_suspend = NULL;
      on_repaint = NULL;
      on_key = NULL;
      on_mouse_in_window = NULL;
      on_pause = NULL;
      on_resume = NULL;
    }

    void set_pause( bool value ) {
      if( value == true ) {
        if( pause_count == 0 ) {
          paused = AXE_TRUE;
          if( on_pause != NULL ) {
            on_pause();
          }
        }

        ++pause_count;
      } else {
        if( pause_count > 0 ) {
          --pause_count;
          if( pause_count == 0 ) {
            paused = AXE_FALSE;
            if( on_resume != NULL ) {
              on_resume();
            }
          }
        }
      }
    }

    ~axwd_state() {
    }
};
#endif // __AXWD_STATE_H__

/* $Id: axwd_state.h,v 1.1 2004/06/09 18:23:59 doneval Exp $ */
