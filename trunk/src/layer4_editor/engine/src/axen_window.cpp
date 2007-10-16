/**
* @file
* Application singleton
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      11 Sep 2004
*/
#include "axen_window.h"


bool axen_window::          active = false;
axen_window *axen_window::  instance = NULL;

/*$1- Constructor & Destructor -----------------------------------------------*/

/**
* Constructor
*/
axen_window::axen_window()
{
  axwd_on_start( axen_window::init );
  axwd_on_main_loop( axen_window::loop );
  axwd_on_end( axen_window::done );

  fullscreen = false;
  set_fullscreen( true );

  set_name( "Axe engine" );

  show_cursor = false;
  set_cursor_visible( true );
}

/**
* Destructor
*/
axen_window::~axen_window()
{
  active = false;
  axwd_on_start( NULL );
  axwd_on_main_loop( NULL );
  axwd_on_end( NULL );
}

/*$1- Singleton stuff --------------------------------------------------------*/

/**
* Singleton creator
*/
axen_window *axen_window::create()
{
  if( active == false )
  {
    instance = new axen_window;
    active = true;
  }

  return( instance );
}

/*$1- Execution flux ---------------------------------------------------------*/

/**
* Create the window and start looping
*/
int axen_window::start( HINSTANCE instance )
{
  axwd_start_application( instance );
  return( AXE_TRUE );
}

/**
* Pause all window activity
*/
int axen_window::pause( bool pause )
{
  if( true == pause )
  {
    axwd_pause_application();
  }
  else
  {
    axwd_resume_application();
  }

  return( AXE_TRUE );
}

/**
* End all window activity
*/
int axen_window::end()
{
  axwd_end_application();
  return( AXE_TRUE );
}

/*$1- Events callbacks -------------------------------------------------------*/

/**
* Start window
*/
int axen_window::init()
{
  return( engine->start_window() );
}

/**
* End window
*/
int axen_window::done()
{
  return( engine->end_window() );
}

/**
* Each loop iteration
*/
int axen_window::loop()
{
  return( engine->loop_window() );
}

/*$1- Configuration ----------------------------------------------------------*/

/**
* Set window to fullscreen
*/
void axen_window::set_fullscreen( bool set_fullscreen )
{
  set_fullscreen = AXE_TO_BOOL( set_fullscreen );

  if( set_fullscreen != fullscreen )
  {
    fullscreen = set_fullscreen;
    if( true == fullscreen )
    {
      axwd_change_to_fullscreen();
    }
    else
    {
      axwd_change_to_windowed();
    }
  }
}

/**
* Ask if window is in fullscreen mode
*/
bool axen_window::is_fullscreen() const
{
  return( fullscreen );
}

/**
* Set application name
*/
void axen_window::set_name( const axe_string& application_name ) const
{
  axwd_set_window_title( application_name );
  axwd_set_application_name( application_name );
}

/**
* Hide or show the cursor
*/
void axen_window::set_cursor_visible( bool show )
{
  show = AXE_TO_BOOL( show );

  if( show_cursor != show )
  {
    show_cursor = show;
    axwd_show_cursor( (int) show );
  }
}

/**
* Ask is cursor is visible
*/
bool axen_window::is_cursor_visible() const
{
  return( show_cursor );
}

/**
* Get window handle
*/
HWND axen_window::get_window() const
{
  return( axwd_get_windows_info().window );
}

/**
* Get instance
*/
HINSTANCE axen_window::get_instance() const
{
  return( axwd_get_windows_info().instance );
}

/**
* Get instance
*/
HDC axen_window::get_device() const
{
	return( axwd_get_windows_info().device_context );
}

/**
* Get instance
*/
const screen_info axen_window::get_screen_size() const
{
	return( axwd_get_screen_info() );
}


/* $Id: axen_window.cpp,v 1.1 2004/09/20 21:28:14 doneval Exp $ */
