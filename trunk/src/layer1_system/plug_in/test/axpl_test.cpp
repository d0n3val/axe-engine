/**
* @file
* Axe 'plug in' test code
* @see axe_events.h
*/
#include "axpl_test.h"

#define AXPL_NO_AUTOLINK
#include "axe_plug_in.h"

/// Version of this test code
#define AXE_PLUG_IN_TEST_VERSION  1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_plug_in.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_plug_in.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line )
{
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axpl_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions()
{
  printf( "\nGetting lib version ... " );

  int lib_version = axpl_get( AXPL_VERSION );

  if( lib_version != AXE_PLUG_IN_TEST_VERSION )
  {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_PLUG_IN_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_PLUG_IN_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main()
{
  printf( "Axe 'plug in' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 )
  {
    return( 0 );
  }

  // Start ---------------------------------------------
  printf( "\nLoading axe_randomizer.dll plug-in ..." );

  AXE_ID  lib_id = axpl_load( "axe_randomizer" );
  printf( "OK, ID = %d", lib_id );

  printf( "\nCalling func 'roll'..." );

  typedef void  func_init( const unsigned long seed );
  typedef int   func_roll( const int, const int );

  func_init*    init = (func_init*) axpl_get_function( lib_id, "axrd_set_seed" );
  func_roll*    roll = (func_roll*) axpl_get_function( lib_id, "axrd_roll" );

  int a = is_plug_in_loaded(".\\axe_randomizer");

  init(4111);
  printf( "%d", roll(3, 6) );

  printf( "\nUnloading plug-in ..." );
  axpl_unload( lib_id );
  printf( "OK" );

  getchar();

  // Finish --------------------------------------------
  printf( "\nAxe 'plug in' library test FINISHED\n" );

  return( 1 );
}

/* $Id: axpl_test.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
