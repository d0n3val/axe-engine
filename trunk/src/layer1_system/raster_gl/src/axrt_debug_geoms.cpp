/**
* @file
* Debug geoms like sphere, axis, lines, arrow, plane, etc ...
*/
#include "axrt_stdafx.h"

/**
* draw_axis
* Will draw a typical Axis, as seen in 3d Studio or such. Apply "use_matrix" before calling it
* to put in the rotation/position you want
*/
int axrt_draw_axis( const float size )
{
  AXE_CHECK_DBG_ERROR( (state.ready_to_draw == true), 15 );

  glBegin( GL_LINES );
  glColor3f( (GLfloat) 1.0f, 0, 0 );
  glVertex3f( 0, 0, 0 );
  glVertex3f( (GLfloat) size, 0, 0 );
  glColor3f( 0, (GLfloat) 1.0f, 0 );
  glVertex3f( 0, 0, 0 );
  glVertex3f( 0, (GLfloat) size, 0 );
  glColor3f( 0, 0, (GLfloat) 1.0f );
  glVertex3f( 0, 0, 0 );
  glVertex3f( 0, 0, (GLfloat) size );
  glColor3f( (GLfloat) 1.0f, (GLfloat) 1.0f, (GLfloat) 1.0f );
  glEnd();

  return( AXE_TRUE );
}

/* $Id: axrt_raster.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
