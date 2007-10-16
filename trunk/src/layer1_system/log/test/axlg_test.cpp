/**
* @file
* Axe 'log' test code
* @see axe_log.h
*/
#include "axlg_test.h"

#define AXLG_NO_AUTOLINK
#include "../src/axe_log.h"

/// Version of this test code
#define AXE_LOG_TEST_VERSION  1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_log.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_log.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line ) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axlg_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axlg_get( AXLG_VERSION );

  if( lib_version != AXE_LOG_TEST_VERSION ) {
    printf( "This test program and the library versions differ! Lib:%d Test:%d\n", lib_version, AXE_LOG_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_LOG_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'log' library test START\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  void *p = NULL;
  
  SetLastError(0);
  AXE_ASSERT( p != NULL, "invalid argument" );
  /*

  // Start -------------------------------------------
  AXE_INFO( "info %s prueba %d", "de", 1234 );
  AXE_INFO( "info %s prueba %d", "de", 1234 );
  AXE_INFO( "info %s prueba %d", "de", 1234 );
  AXE_INFO( "info %s prueba %d", "de", 1234 );
  AXE_INFO( "info %s prueba %d", "de", 1234 );

  AXE_WARNING( "warning %s prueba %d", "de", 1234 );
  AXE_WARNING( "warning %s prueba %d", "de", 1234 );

  AXE_ERROR( "error %s prueba %d", "de", 1234 );
  AXE_WARNING( "warning %s prueba %d", "de", 1234 );
  AXE_WARNING( "warning %s prueba %d", "de", 1234 );
  AXE_ERROR( "error %s prueba %d", "de", 1234 );

  AXE_INFO( "info %s prueba %d", "de", 1234 );
  AXE_INFO( "info %s prueba %d", "de", 1234 );
*/
  // Finish -------------------------------------------
  printf( "\nAXE 'log' library test FINISH\n" );
  getchar();
}

/* $Id: axlg_test.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
