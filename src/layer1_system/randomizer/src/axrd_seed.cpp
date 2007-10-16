/**
* @file
* Get / Set the randomizer seed
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 Apr 2004
*/
#include "axrd_stdafx.h"

/**
* Sets current seed and generates random numbers
*/
AXRD_API void axrd_set_seed( const unsigned long seed ) {
  // Disconnect "fixed data" mode
  state.fixed_data_mode = false;

  // set current seed
  state.randomizer.init(seed);

  // create some random numbers for future use
  for( register int i = 0; i < AXRD_BUFFER_SIZE; ++i ) {
    state.numbers[i] = state.randomizer.get_ulong();
  }

  state.init = true;
}

/**
* Gets current seed
*/
AXRD_API unsigned long axrd_get_seed(  ) {
  if ( state.fixed_data_mode ) {
    return(state.fixed_seed);
  } else {
    return(state.randomizer.seed);
  }
}

/* $Id: axrd_seed.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
