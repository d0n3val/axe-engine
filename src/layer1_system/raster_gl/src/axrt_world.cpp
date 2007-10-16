/**
* @file
* Misc world matrix functions
*/
#include "axrt_stdafx.h"

/**
* Set viewport. Call this function every time windows resizes
*/
AXRT_API int axrt_set_viewport( int x, int y, int width, int height )
{
  AXE_CHECK_DBG_ERROR( (state.init == true), 10 );

  state.wpc_data.viewport.x = x;
  state.wpc_data.viewport.y = y;
  state.wpc_data.viewport.width = width;
  state.wpc_data.viewport.height = height;

  state.wpc_data.viewport.init = true;

  return( AXE_TRUE );
}

/**
* Set projection
*/
AXRT_API int axrt_set_perspective( float fov, float aspect, float z_near, float z_far )
{
  AXE_CHECK_DBG_ERROR( (state.init == true), 10 );

  state.wpc_data.perspective.fov = fov;
  state.wpc_data.perspective.aspect = aspect;
  state.wpc_data.perspective.z_near = z_near;
  state.wpc_data.perspective.z_far = z_far;

  state.wpc_data.perspective.init = true;

  return( AXE_TRUE );
}

/**
* Set view
*/
AXRT_API int axrt_set_view( float look[3], float pos[3], float up[3] )
{
  AXE_CHECK_DBG_ERROR( (state.init == true), 10 );

  memcpy( state.wpc_data.camera.look, look, sizeof(float) * 3 );
  memcpy( state.wpc_data.camera.pos, pos, sizeof(float) * 3 );
  memcpy( state.wpc_data.camera.up, up, sizeof(float) * 3 );

  state.wpc_data.camera.init = true;

  return( AXE_TRUE );
}

/**
* Set all data needed to start sending geometry
*/
AXRT_API int axrt_prepare_to_draw()
{
  AXE_CHECK_DBG_ERROR( (state.init == true), 10 );
  AXE_CHECK_DBG_ERROR( (state.wpc_data.viewport.init == true), 12 );
  AXE_CHECK_DBG_ERROR( (state.wpc_data.perspective.init == true), 13 );
  AXE_CHECK_DBG_ERROR( (state.wpc_data.camera.init == true), 14 );

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  state.wpc_data.viewport.exec();
  state.wpc_data.perspective.exec();
  state.wpc_data.camera.exec();

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  if( state.wireframe == true )
  {
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  }
  else
  {
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  }

  state.ready_to_draw = true;

  return( AXE_TRUE );
}

/**
* Draw scene
*/
AXRT_API int axrt_draw()
{
  AXE_CHECK_DBG_ERROR( (state.ready_to_draw == true), 15 );

  int result = SwapBuffers( state.context );
  state.ready_to_draw = false;

  return( result );
}

/**
* Set wireframe
*/
AXRT_API int axrt_set_wireframe( int wireframe )
{
  state.wireframe = AXE_TO_BOOL( wireframe );
  return( AXE_TRUE );
}

/* $Id: axrt_raster.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
