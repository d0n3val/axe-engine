/**
* @file
* Axe 'file_system' test code
* @see axe_file_system.h
*/
#include "axfs_test.h"

#define AXFS_NO_AUTOLINK
#include "../src/axe_file_system.h"

/// Version of this test code
#define AXE_FILE_SYSTEM_TEST_VERSION  1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_file_system.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_file_system.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error(int num, const char *file, long line) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axfs_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axfs_get( AXFS_VERSION );

  if( lib_version != AXE_FILE_SYSTEM_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_FILE_SYSTEM_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_FILE_SYSTEM_TEST_VERSION );

  return( 1 );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'file_system' library test STARTED\n" );

  /*$1- Check versions -------------------------------------------------------*/
  if( check_versions() == 0 ) {
    return( 0 );
  }

  axfs_set_error_callback(error);

  /*$1- Start ----------------------------------------------------------------*/
  /* 
  AXFS_API const void*  axfs_get_data( const AXE_ID file_id, const int reload );
  AXFS_API int          axfs_set_data( const AXE_ID file_id, const void* data, const size_t size );
  AXFS_API int          axfs_add_data( const AXE_ID file_id, const void* data, const size_t size );
  AXFS_API int          axfs_insert_data( const AXE_ID file_id, const void* data, const size_t size, const size_t pos );
*/

  /*$1- Test directory functions ---------------------------------------------*/
  printf( "\nCurrent dir of work is: %s ", axfs_get_current_dir() );

  printf( "\nchdir ../layer1_system/file_system/test " );
  axfs_change_dir( "../layer1_system/file_system/test" );

  printf( "\nCurrent dir of work is: %s ", axfs_get_current_dir() );

  printf( "\nmkdir my_test_dir " );
  axfs_create_dir( "my_test_dir" );

  printf( "\nrmdir my_test_dir " );
  axfs_remove_dir( "my_test_dir" );

  /*$1- Utils test -----------------------------------------------------------*/
  printf( "\nCheck if 'test.txt' exists (must be 1): %d ", axfs_file_exists("test.txt") );

  printf( "\n'test.txt' size is (must be 15): %d bytes ", axfs_file_size("test.txt") );

  printf( "\nrename 'test.txt' to 'my_test.txt' " );
  axfs_rename_file( "test.txt", "my_test.txt" );

  printf( "\nrename 'my_test.txt' to 'test.txt' " );
  axfs_rename_file( "my_test.txt", "test.txt" );

  /*$1- file managment test --------------------------------------------------*/
  AXE_ID  file1;

  AXE_ID  file2;

  AXE_ID  file3;

  printf( "\nCreating file1 with 'test.txt' that already exists..." );
  file1 = axfs_create( "test.txt", AXE_FALSE );

  printf( "\nCreating file2 with 'test2.txt' that does not exists..." );
  file2 = axfs_create( "test2.txt", AXE_FALSE );

  printf( "\nCreating file3 with tmp name..." );
  file3 = axfs_create( "", AXE_FALSE );

  printf( "\nfile3 tmp name is: %s ", axfs_get_name(file3) );

  /*$1- Data management ------------------------------------------------------*/
  
  size_t sz = axfs_get_size( file1 );
  printf( "\nfile1 allocated mem is: %d bytes", sz );
  
  char*   buf = new char[sz + 1];
  memcpy( buf, axfs_get_data(file1, AXE_FALSE), sz );
  buf[sz] = 0;

  printf( "\nData inside file1 is: \n%s", buf );

  /*$1- destroy --------------------------------------------------------------*/
  printf( "\nDestroy file1 ..." );
  axfs_destroy( file1, AXE_FALSE );

  printf( "\nDestroy and delete file2 ..." );
  axfs_destroy( file2, AXE_TRUE );

  printf( "\nDestroy file3 ..." );
  //axfs_destroy( file3, AXE_TRUE );

  /*$1- Finish ---------------------------------------------------------------*/
  printf( "\nAxe 'file_system' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axfs_test.cpp,v 1.2 2004/06/09 18:23:55 doneval Exp $ */
