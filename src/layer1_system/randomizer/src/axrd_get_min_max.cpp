/**
* @file
* random number generation from a pre-calculated table
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 Apr 2004
*/
#include "axrd_stdafx.h"

/**
* get a float from the table [min..max]
*/
AXRD_API float axrd_get_float_min_max( const float min, const float max, const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  AXE_ASSERT( max > min );

  return( min + ((float) state.get_d(pos) * (max - min)) );
}

/**
* get a double from the table [min..max]
*/
AXRD_API double axrd_get_double_min_max( const double min, const double max, const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  AXE_ASSERT( max > min );

  return( min + (state.get_d(pos) * (max - min)) );
}

/**
* get an int from the table [min..max]
*/
AXRD_API int axrd_get_int_min_max( const int min, const int max, const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  AXE_ASSERT( max > min );

  return( min + (int) (state.get_d(pos) * (double) (max - min)) );
}

/**
* get an unsigned int from the table [min..max]
*/
AXRD_API unsigned int axrd_get_uint_min_max( const unsigned int min, const unsigned int max, const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  AXE_ASSERT( max > min );

  return( min + (unsigned int) (state.get_d(pos) * (double) (max - min)) );
}

/**
* get a long from the table [min..max]
*/
AXRD_API long axrd_get_long_min_max( const long min, const long max, const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  AXE_ASSERT( max > min );

  return( min + (long) (state.get_d(pos) * (double) (max - min)) );
}

/**
* get an unsigned long from the table [min..max]
*/
AXRD_API unsigned long axrd_get_ulong_min_max( const unsigned long min,
                                               const unsigned long max,
                                               const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  AXE_ASSERT( max > min );

  return( min + (unsigned long) (state.get_d(pos) * (double) (max - min)) );
}

/* $Id: axrd_get_min_max.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
