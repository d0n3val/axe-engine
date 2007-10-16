/**
* @file
* Init and Deinit
*/
#include "axrt_stdafx.h"

/**
* Inits context canvas to start draw
*/
AXRT_API int axrt_create_device( HDC context )
{

  /*$1- Create OpenGL rendering context and check ----------------------------*/
  state.context = context;
  state.rendering_context = wglCreateContext( context );
  AXE_CHECK_ERROR( (state.rendering_context != NULL), 8 );

  /*$1- Make it the current rendering context --------------------------------*/
  int result = wglMakeCurrent( context, state.rendering_context );
  AXE_CHECK_ERROR( (result == TRUE), 9 );

  /*$1- Some standard settings -----------------------------------------------*/
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );
  glShadeModel( GL_SMOOTH );
  glEnable( GL_CULL_FACE );
  glCullFace( GL_BACK );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

  state.init = true;

  return( AXE_TRUE );
}

/**
* Closes canvas
*/
AXRT_API int axrt_release( void )
{
  if( state.init == true && state.rendering_context != NULL )
  {
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( state.rendering_context );
    state.rendering_context = NULL;
    state.init = false;
  }

  return( AXE_TRUE );
}

/* $Id: axrt_raster.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
