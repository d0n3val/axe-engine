/**
* @file
* Axe 'raster' test code
* @see axe_raster.h
*/
#include "axm2_test.h"

#define AXM2_NO_AUTOLINK
#include "axe_raster.h"

/// Version of this test code
#define AXE_M2_LOADER_TEST_VERSION 1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_raster.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_raster.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line )
{
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axm2_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions()
{
  printf( "\nGetting lib version ... " );

  int lib_version = axm2_get( AXM2_VERSION );

  if( lib_version != AXE_M2_LOADER_TEST_VERSION )
  {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_M2_LOADER_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_M2_LOADER_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main()
{
  printf( "Axe 'raster' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 )
  {
    return( 0 );
  }

  // Start ---------------------------------------------
  getchar();

  // Finish --------------------------------------------
  printf( "\nAxe 'raster' library test FINISHED\n" );

  return( 1 );
}

/* $Id: axpl_test.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
