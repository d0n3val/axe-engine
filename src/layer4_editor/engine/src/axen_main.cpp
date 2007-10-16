/**
* @file
* First called function (main)
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      09 Sep 2004
*/
#include "axen_stdafx.h"
#include "axen_window.h"
#include "axen_control.h"

/**
* Main
*/
int __stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR arguments, int nShowCmd )
{
  AXE_INFO( "Starting engine activity" );

  /*$1- Create the engine singleton ------------------------------------------*/
  engine = axen_engine::create();
	mopengl = opengl::create();

  /*$1- Start application ----------------------------------------------------*/
  engine->init();
  engine->get_window()->set_fullscreen(false);
  engine->get_window()->set_cursor_visible(true);
  engine->get_window()->set_name("axe test");
  engine->get_window()->start( hInstance );


  /*$1- End application ------------------------------------------------------*/
  
  int ret = engine->get_window()->end();

  /*$1- Destroy the engine singleton -----------------------------------------*/
  AXE_RELEASE( mopengl );
  AXE_RELEASE( engine );

  if( AXE_TRUE == ret )
  {
    AXE_INFO( "End engine activity [SUCCESS]" );
    return( EXIT_SUCCESS );
  }

  AXE_INFO( "End engine activity [FAILURE]" );
  return( EXIT_FAILURE );
}

/* $Id: axen_main.cpp,v 1.1 2004/09/20 21:28:14 doneval Exp $ */
