/**
* @file
* Control singleton
* @author    Ricard Pillosu <doneval\@users.sf.net>
* @date      18 Sep 2004
*/
#ifndef __AXEN_CONTROL_H__
  #define __AXEN_CONTROL_H__

  #include "axen_stdafx.h"

/**
* Control singleton
*/
class axen_control
{

  /*$1- Singleton stuff ------------------------------------------------------*/
  public:
    static axen_control*  create();
    ~axen_control();
  private:
    static bool           active;
    static axen_control*  instance;
    axen_control();
  public:

  /*$1- Methods --------------------------------------------------------------*/
  public:
    void  init( HWND window, HINSTANCE instance );
    void  update( float elapsed_time );
    void  done();

    void  add_alert( AXE_ID event_id, unsigned int key );
    bool  is_key_down( unsigned int key ) const;
    void  get_mouse_steering( int *x, int *y ) const;

  /*$1- Properties -----------------------------------------------------------*/
  private:
    int keyboard_id;
    int mouse_id;
};
#endif // __AXEN_CONTROL_H__

/* $Id: axen_control.h,v 1.1 2004/09/20 21:28:14 doneval Exp $ */
