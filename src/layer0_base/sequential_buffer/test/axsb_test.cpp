/**
* @file
* Axe 'string' test code
* @see axe_string.h
*/
#include "axst_test.h"

#define AXST_NO_AUTOLINK
#include "../src/axe_string.h"

/*$1- Version of this test code ----------------------------------------------*/
#define AXE_STRING_TEST_VERSION 1

/*$1- Use proper library -----------------------------------------------------*/
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_string.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_string.lib" )
#endif

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  if( AXE_STRING_VERSION != AXE_STRING_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      AXE_STRING_VERSION,
      AXE_STRING_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This Test Version: %d\n\n", AXE_STRING_VERSION, AXE_STRING_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe '%s' library test STARTED\n", AXE_STRING_NAME );

  /*$1- Check versions -------------------------------------------------------*/
  if( check_versions() == 0 ) {
    return( 0 );
  }

  /*$1- Start ----------------------------------------------------------------*/
  printf( "\nCreating 'test' string ... \n" );

  axst_string str1( "test" );
  printf( "RESULT 1: [%s] ", str1 );

  printf( "\nCreating 'Hello World' formatted string ... \n" );

  axst_string str2( "Hello %s", "world" );
  printf( "RESULT 2: [%s] ", str2 );

  printf( "\nCreating a copy from previous string ... \n" );

  axst_string str3( str2 );
  printf( "RESULT 3: [%s] ", str3 );

  /*$1------------------------------------------------------------------------*/
  printf( "\nAdding 'Bye world' to string 2 ... \n" );
  str2 += "Bye world";
  printf( "RESULT 2: [%s] ", str2 );

  printf( "\nAdding formatted 'Bye 1234' to string 3 ... \n" );
  str3.add( "Bye %d", 1234 );
  printf( "RESULT 3: [%s] ", str3 );

  printf( "\nAdding string 3 to string 2 ... \n" );
  str2 += str3;
  printf( "RESULT 2: [%s] ", str2 );

  /*$1------------------------------------------------------------------------*/
  int cmp;

  printf( "\nComparing string 2 with 'not the same' ... \n" );
  cmp = ( str2 == "not the same" );
  printf( "RESULT: [%s] ", (cmp == 1) ? "true" : "false" );

  printf( "\nComparing string 3 with 'Hello worldBye 1234' ... \n" );
  cmp = ( str3 == "Hello worldBye 1234" );
  printf( "RESULT: [%s] ", (cmp == 1) ? "true" : "false" );

  printf( "\nComparing string 3 with 'HELLO WORLDBYE 1234' (case sensitive) ... \n" );
  cmp = ( str3.compare_no_case("HELLO WORLDBYE 1234") );
  printf( "RESULT: [%s] ", (cmp == 1) ? "true" : "false" );

  printf( "\nComparing between string 2 and string 3 ... \n" );
  cmp = str3 == str2;
  printf( "RESULT: [%s] ", (cmp == 1) ? "true" : "false" );

  /*$1------------------------------------------------------------------------*/
  unsigned int  size;

  printf( "\nGetting size for string 2 ... \n" );
  size = str2.size;
  printf( "RESULT: [%d] ", size );

  printf( "\nGetting size for string 3 ... \n" );
  size = str3.size;
  printf( "RESULT: [%d] ", size );

  /*$1------------------------------------------------------------------------*/
  printf( "\nTesting str1 againts 't.*' ... \n" );
  cmp = str1.regex( "t.*" );
  printf( "RESULT: [%s] ", (cmp == 1) ? "true" : "false" );

  printf( "\nTesting str1 againts 't[abcde].$' ... \n" );
  cmp = str1.regex( "t[abcde].$" );
  printf( "RESULT: [%s] ", (cmp == 1) ? "true" : "false" );

  /*$1------------------------------------------------------------------------*/
  printf( "\nreplace test ...\n" );
  cmp = str3.regex_replace( "world", "i found: \\0 jeje", str2 );
  printf( "RESULT: [%s] ", str2 );

  /*$1- Finish ---------------------------------------------------------------*/
  printf( "\n\nAxe 'string' library test FINISHED\n" );
  getchar();

  return( 1 );
}

/* $Id: axsb_test.cpp,v 1.1 2004/08/22 21:09:00 ilgenio Exp $ */
