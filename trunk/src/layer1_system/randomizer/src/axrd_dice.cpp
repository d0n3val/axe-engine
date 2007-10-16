/**
* @file
* Shortcut functions to roll dice/s
*/
#include "axrd_stdafx.h"

/**
* Roll dice_count x sides
*/
AXRD_API int axrd_roll( const int sides, const int dice_count, const long pos ) {
  register int  i;
  float         s = (float) sides - 1.0f;
  float         value = (float) dice_count;

  for( i = 0; i < dice_count; ++i ) {
    value += (float) state.get_d( pos ) * s;
  }

  return( (int) ceilf(value) );
}

/**
* Return the diference with the number-to-hit
*/
AXRD_API int axrd_percent( const int percent, const long pos ) {
  return( (int) ceil( (state.get_d(pos) - ((double) percent * 0.01)) * 100.0) );
}

/* $Id: axrd_dice.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
