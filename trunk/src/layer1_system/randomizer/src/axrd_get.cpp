/**
* @file
* random number generation from a pre-calculated table
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 Apr 2004
*/
#include "axrd_stdafx.h"

/**
* get a float from the table [0..1]
*/
AXRD_API float axrd_get_float( const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  return( (float) state.get_d(pos) );
}

/**
* get a double from the table [0..1]
*/
AXRD_API double axrd_get_double( const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  return( state.get_d(pos) );
}

/**
* get an int from the table [MIN_INT..MAX_INT]
*/
AXRD_API int axrd_get_int( const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  return( (int) state.get_l(pos) );
}

/**
* get an unsigned int from the table [0..MAX_UINT]
*/
AXRD_API unsigned int axrd_get_uint( const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  return( (unsigned int) state.get_ul(pos) );
}

/**
* get a long from the table [MIN_LONG..MAX_LONG]
*/
AXRD_API long axrd_get_long( const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  return( (unsigned int) state.get_l(pos) );
}

/**
* get an unsigned long from the table [0..MAX_ULONG]
*/
AXRD_API unsigned long axrd_get_ulong( const unsigned long pos ) {
  AXE_CHECK_DBG_ERROR( state.init, 8 );
  return( (unsigned int) state.get_ul(pos) );
}

/* $Id: axrd_get.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
