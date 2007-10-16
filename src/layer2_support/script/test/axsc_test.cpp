/**
* @file
* Axe 'script' test code
* @see axe_script.h
*/
#include "axsc_test.h"

#define AXSC_NO_AUTOLINK
#include "../src/axe_script.h"

/// Version of this test code
#define AXE_SCRIPT_TEST_VERSION 1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_script.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_script.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line ) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axsc_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axsc_get( AXSC_VERSION );

  if( lib_version != AXE_SCRIPT_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_SCRIPT_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_SCRIPT_TEST_VERSION );

  return( 1 );
}

void print_text( int num ) {
  printf( "FROM SCRIPT-> %d", num );
}

struct some_data
{
  int   a;
  float b;
  float  c;

  void some_method(int n) {
    a = n;

  }
};

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'script' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  // Start ---------------------------------------------
  int var_to_publish = 43;
  int result;
  int a = 1;
  int b = 99;
  int c = 1;

  some_data test;

  test.a = 5;
  test.b = 23.221312f;
  test.c = 89.0f;

  // Init the engine ---
  axsc_init();

  // Configure the engine ---
  axsc_register_variable( "int var", &var_to_publish );
  axsc_register_function( "void print_text(int)", AXSC_FUNCTION(print_text) );

  axsc_begin_register_class( "some_data", sizeof(some_data) );
  axsc_register_property( "int a", AXSC_OFFSET(some_data, a) );
  axsc_register_property( "float b", AXSC_OFFSET(some_data, b) );
  axsc_register_property( "float c", AXSC_OFFSET(some_data, c) );

  axsc_register_method("void some_method(int)", AXSC_METHOD(some_data, some_method));
  axsc_end_register_class();

  axsc_register_variable( "some_data test", &test );

  // Load all scripts ---
  axsc_load_file( "../layer2_support/script/test/test.axe" );

  // Compile scripts ---
  axsc_compile();

  // Call a function ---
  axsc_begin_call_function( "main" );
  axsc_add_argument( &a, sizeof(a) );
  axsc_add_argument( &b, sizeof(b) );
  axsc_add_argument( &c, sizeof(c) );
  axsc_set_return_value( &result, sizeof(result) );
  axsc_end_call_function();

  // End using the script engine ---
  axsc_done();

  // check data ---
  printf( "\nVar now contains %d\n", var_to_publish );
  printf( "\nScript returned %d\n", result );

  // Finish --------------------------------------------
  printf( "\nAxe 'script' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axsc_test.cpp,v 1.2 2004/09/10 23:06:47 doneval Exp $ */
