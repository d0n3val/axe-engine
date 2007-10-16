/**
* @file
* A random file generator usign Marsenne Twister
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 Apr 2004
* @see       http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
*/
#ifndef __AXRD_MT_RAND_H__
  #define __AXRD_MT_RAND_H__

/*$1- Period parameters ------------------------------------------------------*/
  #define N           624
  #define M           397
  #define MATRIX_A    0x9908b0dfUL                  /// constant vector a
  #define UPPER_MASK  0x80000000UL                  /// most significant w-r bits
  #define LOWER_MASK  0x7fffffffUL                  /// least significant r bits
  #define DOUBLE_MUL  2.32830643370807973754314e-10 /// 1 / 2^32

/**
* A random number generator class using Marsenne Twister
*/
class mt_rand
{
  public:
    unsigned long         mt[N];  /// the array for the state vector
    int                   mti;    /// mti==N+1 means mt[N] is not initialized
    const unsigned long&  seed;
  private:
    unsigned long _seed;
  public:
    mt_rand();
    ~mt_rand();

    void              init( unsigned long seed );
    long              get_long();
    unsigned long     get_ulong();
    double            get_double();

    mt_rand &operator =( const mt_rand& randomizer );
};
#endif // __AXRD_MT_RAND_H__

/* $Id: axrd_mt_randomizer.h,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
