/**
* @file
* Debug geoms like sphere, axis, lines, arrow, plane, etc ...
*/
#include "axrt_stdafx.h"

/**
* load_texture
*/
AXE_ID axrt_load_texture( const char* file_name )
{
  AXE_ID  tex_id = SOIL_load_OGL_texture( file_name, 0, 0, SOIL_FLAG_POWER_OF_TWO );
  return( tex_id );
}

/* $Id: axrt_raster.cpp,v 1.1 2004/09/24 17:58:39 doneval Exp $ */
