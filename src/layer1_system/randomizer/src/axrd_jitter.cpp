/**
* @file
* Simple functions to add jitter to numbers
*/
#include "axrd_stdafx.h"

/**
* Apply a +-jitter to a single value
*/
AXRD_API void axrd_jitter( float& value, const float jitter, const long pos ) {
  value = ( value - jitter ) + ( (float) state.get_d(pos) * (jitter * 2.0f) );
}

/**
* Apply a jitter to an array of values
*/
AXRD_API void axrd_jitter_array( float* values, const int values_count, const float jitter, const long pos ) {
  register int  i;

  for( i = 0; i < values_count; ++i ) {
    values[i] = ( values[i] - jitter ) + ( (float) state.get_d(pos) * (jitter * 2.0f) );
  }
}

/* $Id: axrd_jitter.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
