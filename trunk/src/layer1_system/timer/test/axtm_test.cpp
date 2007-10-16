/**
* @file
* Axe 'timer' test code
* @see axe_timer.h
*/
#include "axtm_test.h"

#define AXTM_NO_AUTOLINK
#include "../src/axe_timer.h"

/// Version of this test code
#define AXE_TIMER_TEST_VERSION  1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_timer.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_timer.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line ) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axtm_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axtm_get( AXTM_VERSION );

  if( lib_version != AXE_TIMER_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_TIMER_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_TIMER_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'timer' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  // Start ---------------------------------------------
  AXE_ID timer;

  printf( "Creating a timer ..." );
  timer = axtm_create();

  printf( "Starting the timer ..." );
  axtm_start(timer);

  printf( "Waiting 1.1 sec ..." );

  Sleep( 1100 );

  printf( "Stopping the timer ..." );

  float e = axtm_stop(timer);

  printf( "Elapsed: %f Elapsed CPU Ticks: %u", e, axtm_elapsed_ticks(timer) );

  // Finish --------------------------------------------
  printf( "\nAxe 'timer' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axtm_test.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
