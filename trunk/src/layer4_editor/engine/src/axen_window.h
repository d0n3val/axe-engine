/**
* @file
* Application singleton
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      11 Sep 2004
*/
#ifndef __AXEN_WINDOW_H__
  #define __AXEN_WINDOW_H__

  #include "axen_stdafx.h"

/**
* Window singleton
*/
class axen_window
{

  /*$1- Singleton stuff ------------------------------------------------------*/
  public:
    static axen_window*   create();
    ~axen_window();
  private:
    static bool           active;
    static axen_window*   instance;
    axen_window();
  public:

    /*$1- Window execution flux ----------------------------------------------*/
    int start( HINSTANCE instance );
    int pause( bool pause );
    int end();

    /*$1- Events callbacks ---------------------------------------------------*/
    static int  init();
    static int  done();
    static int  loop();

    /*$1- Configuration ------------------------------------------------------*/
    void  set_fullscreen( bool set_fullscreen );
    bool  is_fullscreen() const;

    void  set_name( const axe_string& application_name ) const;
    void  set_cursor_visible( bool show );
    bool  is_cursor_visible() const;

    /*$1- Gets ---------------------------------------------------------------*/
    HWND              get_window() const;
    HINSTANCE         get_instance() const;
    HDC               get_device() const;
    screen_info const get_screen_size() const;
  private:

    /*$1- Properties ---------------------------------------------------------*/
    bool  fullscreen;
    bool  show_cursor;
};
#endif // __AXEN_WINDOW_H__

/* $Id: axen_window.h,v 1.1 2004/09/20 21:28:14 doneval Exp $ */
