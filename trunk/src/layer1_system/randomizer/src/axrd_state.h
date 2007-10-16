/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXRD_STATE_H__
  #define __AXRD_STATE_H__

  #include "axrd_stdafx.h"
  #include "axrd_mt_randomizer.h"

  #define AXRD_DEFAULT_SEED 5489UL

/**
* This class stores all data related to the state of the library
*/
class axrd_state : public axe_state
{
  public:
    unsigned long numbers[AXRD_BUFFER_SIZE];  /// pool of random numbers
    int           pos;                        /// current pos in the pool
    bool          init;                       /// have we generated the random table ?
    mt_rand       randomizer;                 /// class to generate MT pseudo random numbers
    bool          fixed_data_mode;            /// the numbers are generated or fixed externally?
    unsigned long fixed_seed;                 /// seed setted externally
  public:

    /**
    * Constructor
    */
    axrd_state() :
    axe_state() {
      lib_id = 'AXRD';
      strcpy_s( lib_name, LIB_NAME_LONG, "Randomizer" );
      lib_version = 1;
      pos = -1;
      init = false;
      fixed_data_mode = false;
      fixed_seed = AXRD_DEFAULT_SEED;
    }

    /**
    * Destructor
    */
    ~axrd_state() {
    }

    /**
    * Step one position in the table
    */
    inline void step_pos( const long new_pos ) {
      AXE_ASSERT( init );

      if( new_pos > 0 ) {
        pos = (int) new_pos % AXRD_BUFFER_SIZE;
      } else if( ++pos >= AXRD_BUFFER_SIZE ) {
        pos = 0;
      }
    }

    /**
    * returns a unsigned long from the table
    */
    inline unsigned long get_ul( const long new_pos ) {
      step_pos( new_pos );
      return( numbers[pos] );
    }

    /**
    * Returns a long from the table
    */
    inline long get_l( const long new_pos ) {
      step_pos( new_pos );
      return( (long) numbers[pos] >> 1 );
    }

    /**
    * returns a double from the table [0..1]
    */
    inline double get_d( const long new_pos ) {
      step_pos( new_pos );
      return( (double) numbers[pos] * (1.0 / 4294967295.0) );
    }
};
#endif // __AXRD_STATE_H__

/* $Id: axrd_state.h,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
