/**
* @file
* Axe 'randomizer' test code
* @see axe_randomizer.h
*/
#include "axrd_test.h"

#define AXRD_NO_AUTOLINK
#include "../src/axe_randomizer.h"

/// Version of this test code
#define AXE_RANDOMIZER_TEST_VERSION 1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_randomizer.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_randomizer.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line ) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axrd_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axrd_get( AXRD_VERSION );

  if( lib_version != AXE_RANDOMIZER_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_RANDOMIZER_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_RANDOMIZER_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'randomizer' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  // Start ---------------------------------------------
  float tmp;
  int   tmpi;

  axrd_set_seed( 30869UL );

  printf( "\nGet a float random number (0.0..1.0):\t\t" );
  tmp = axrd_get_float();
  printf( "%f ", tmp );

  printf( "\nGet a float random number (-222.0..333.0):\t" );
  tmp = axrd_get_float_min_max( -222.0f, 333.0f );
  printf( "%f ", tmp );

  printf( "\nGet a integer random number:\t\t" );
  tmpi = axrd_get_int();
  printf( "%i ", tmpi );

  printf( "\nGet a integer random number (-18..-12):\t\t" );
  tmpi = axrd_get_int_min_max( -18, -12 );
  printf( "%i ", tmpi );

  // jitter -------------------------------------------
  printf( "\nApply a jitter of 10.0 to a value of 0.0:\t" );
  tmp = 0.0f;
  axrd_jitter( tmp, 10.f );
  printf( "%f ", tmp );

  float v[3];
  v[0] = 1.0f;
  v[1] = 2.0f;
  v[2] = 3.0f;

  printf( "\nApply a jitter of 5.0 to a values of (1.0,2.0,3.0):\n" );
  axrd_jitter_array( v, 3, 5.0f );
  printf( "%f %f %f", v[0], v[1], v[2] );

  // dice --------------------------------------------------------
  printf( "\nRolling 3d6 dice (3..18):\t\t\t" );
  tmpi = axrd_roll( 6, 3 );
  printf( "%i ", tmpi );

  printf( "\nAsking for a 45 percent prob:\t\t\t" );
  tmpi = axrd_percent( 45 );
  printf( "%i ", tmpi );

  // Finish --------------------------------------------
  printf( "\nAxe 'randomizer' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axrd_test.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
