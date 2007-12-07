/**
* @file
* Axe 'python' test code
* @see axe_python.h
*/
#include "axpy_test.h"

#define AXPY_NO_AUTOLINK
#include "axe_python.h"

/// Version of this test code
#define AXE_PYTHON_TEST_VERSION 1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_python.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_python.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line )
{
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axpy_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions()
{
  printf( "\nGetting lib version ... " );

  int lib_version = axpy_get( AXPY_VERSION );

  if( lib_version != AXE_PYTHON_TEST_VERSION )
  {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_PYTHON_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_PYTHON_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main()
{
  printf( "Axe 'python' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 )
  {
    return( 0 );
  }

  axpy_init();

  // Start ---------------------------------------------
  getchar();

  // Test ----------------------------------------------
  printf( "\nExecuting print 'hello world'...\n" );
  axpy_exec( "print 'hello world'" );

  // Test ----------------------------------------------
  printf( "\nLoading script_test.py and executing foo() function...\n" );
  if( axpy_load_file( "script_test", "foo" ) == AXE_FALSE )
  {
    printf( "\nFAIL\n" );
    axpy_finalize();
    return( 0 );
  }
  
  // Test ----------------------------------------------
  printf( "\nExecuting function 'foo()' included in script_test.py, should print 'Im foo from test.py'\n" );
  axpy_exec( "import script_test\nfoo()" );

  // Finish --------------------------------------------
  axpy_finalize();
  printf( "\nAxe 'python' library test FINISHED\n" );
  getchar();

  return( 1 );
}

/* $Id: axpl_test.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
