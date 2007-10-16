/**
* @file
* Axe 'primitives' test code
* @see axe_primitives.h
*/
#include "axpr_test.h"

#define AXPR_NO_AUTOLINK
#include "../src/axe_primitives.h"

/// Version of this test code
#define AXE_PRIMITIVES_TEST_VERSION 1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../output_debug/lib/primitives.lib" )
#else
  #pragma comment( lib, "../output_release/lib/primitives.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
int check_error() {
  int error = axpr_get( AXPR_LAST_ERROR );

  if( error != 0 ) {
    printf( "Error: %s\n", axpr_get_error_message(error) );
    getchar();
    return( 0 );
  }

  printf( "OK\n" );
  return( 1 );
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axpr_get( AXPR_VERSION );

  if( !check_error() ) {
    return( 0 );
  }

  if( lib_version != AXE_PRIMITIVES_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_PRIMITIVES_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_PRIMITIVES_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'primitives' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  // Start ---------------------------------------------
  // Finish --------------------------------------------
  printf( "\nAxe 'primitives' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axp2_test.cpp,v 1.1 2004/08/29 18:28:45 doneval Exp $ */