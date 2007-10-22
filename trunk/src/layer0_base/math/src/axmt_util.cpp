/**
* @file
* Util math functions
*/
#include "axmt_stdafx.h"

float axmt_wrap_pi( const float& angle ) {
  float a = angle;

  a += PI;
  a -= floorf( a * INV_TWO_PI ) * TWO_PI;
  a -= PI;
  return( a );
}

/* $Id: axmt_util.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */