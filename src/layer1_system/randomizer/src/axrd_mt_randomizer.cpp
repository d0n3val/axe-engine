/**
* @file
* A random file generator usign Marsenne Twister
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 Apr 2004
*/
#include "axrd_mt_randomizer.h"
#include <limits.h>

/**
* Constructor
*/
mt_rand::mt_rand() : seed( _seed ) {
  _seed = 5489UL;
  mti = N + 1;
}

/**
* Destructor
*/
mt_rand::~mt_rand() {
}

/**
* Init from seed
*/
void mt_rand::init( const unsigned long randomizer_seed ) {

  // save the seed
  _seed = randomizer_seed;

  mt[0] = _seed & 0xffffffffUL;
  for( mti = 1; mti < N; mti++ ) {
    mt[mti] = ( 1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti );

    /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
    /* In the previous versions, MSBs of the seed affect   */
    /* only MSBs of the array mt[].                        */
    /* 2002/01/09 modified by Makoto Matsumoto             */
    mt[mti] &= 0xffffffffUL;

    /* for >32 bit machines */
  }
}

/**
* generates a random number on [0,0xffffffff]-interval
*/
unsigned long mt_rand::get_ulong() {
  unsigned long         y;
  static unsigned long  mag01[2];
  mag01[0] = 0x0UL;
  mag01[1] = MATRIX_A;

  /* mag01[x] = x * MATRIX_A  for x=0,1 */
  if( mti >= N ) {

    /* generate N words at one time */
    int kk;

    if( mti == N + 1 ) {

      /* if init_genrand() has not been called, */
      init( _seed );  /* a default initial seed is used */
    }

    for( kk = 0; kk < N - M; kk++ ) {
      y = ( mt[kk] & UPPER_MASK ) | ( mt[kk + 1] & LOWER_MASK );
      mt[kk] = mt[kk + M] ^ ( y >> 1 ) ^ mag01[y & 0x1UL];
    }

    for( ; kk < N - 1; kk++ ) {
      y = ( mt[kk] & UPPER_MASK ) | ( mt[kk + 1] & LOWER_MASK );
      mt[kk] = mt[kk + ( M - N )] ^ ( y >> 1 ) ^ mag01[y & 0x1UL];
    }

    y = ( mt[N - 1] & UPPER_MASK ) | ( mt[0] & LOWER_MASK );
    mt[N - 1] = mt[M - 1] ^ ( y >> 1 ) ^ mag01[y & 0x1UL];

    mti = 0;
  }

  y = mt[mti++];

  /* Tempering */
  y ^= ( y >> 11 );
  y ^= ( y << 7 ) & 0x9d2c5680UL;
  y ^= ( y << 15 ) & 0xefc60000UL;
  y ^= ( y >> 18 );

  return( y );
}

/**
* generates a random number on [0,0xffffffff]-interval
*/
long mt_rand::get_long() {
  return (long) ( get_ulong() >> 1 );
}

/**
* generates a random number on [0,1]-real-interval
*/
double mt_rand::get_double() {
  return( get_ulong() * (1.0 / 4294967295.0) ); // divided by 2^32-1
}

/**
* Copy operator
*/
mt_rand &mt_rand::operator=( const mt_rand& randomizer ) {
  init( randomizer.seed );
  return( *this );
}

/* $Id: axrd_mt_randomizer.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
