/**
* @file
* Gets and Sets the complete lists of random numbers
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 Apr 2004
*/

#include "axrd_stdafx.h"

/**
* Sets the random number list
*/
AXRD_API int axrd_set_data( const unsigned long seed, const unsigned long data[AXRD_BUFFER_SIZE] ) {
  state.fixed_data_mode = true;
  state.init = true;
  state.fixed_seed = seed;
  memcpy(state.numbers, data, sizeof(unsigned long) * AXRD_BUFFER_SIZE);
  return( AXE_TRUE );
}

/**
* Returns the random number list
*/
AXRD_API int axrd_get_data( unsigned long& seed, unsigned long data[AXRD_BUFFER_SIZE] ) {
  AXE_CHECK_DBG_ERROR(state.init, 8);
  seed = axrd_get_seed();
  memcpy(state.numbers, data, sizeof(unsigned long) * AXRD_BUFFER_SIZE);
  return( AXE_TRUE );
}

/* $Id: axrd_data.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
