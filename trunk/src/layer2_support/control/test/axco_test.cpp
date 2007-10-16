/**
* @file
* Axe 'control' test code
* @see axe_control.h
*/
#include "axco_test.h"

#include "axe_control.h"
#include "axe_windows.h"
#include "axe_log.h"

/// Version of this test code
#define AXE_CONTROL_TEST_VERSION  1

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line ) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axco_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axco_get( AXCO_VERSION );

  if( lib_version != AXE_CONTROL_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_CONTROL_TEST_VERSION ); 
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_CONTROL_TEST_VERSION );

  return( 1 );
}

DWORD t;
int   ticks;

/**
* On start app
*/
int start() {
  win_info  info = axwd_get_windows_info();

  AXE_INFO( "Init Control" );
  axco_init( info.window, info.instance );

  int num_dev = axco_get_device_count();
  for( register int i = 0; i < num_dev; ++i ) {
    AXE_INFO( "Device found: %s", axco_get_device_name(i) );
  }

  /*$1- set alerts -----------------------------------------------------------*/
  axco_begin_alert( 0 );
  axco_add_event( 1, 57, AXCO_KEY_RELEASE ); // space bar
  //axco_add_event( 1, 11, AXCO_KEY_RELEASE ); // number 0
  //axco_add_event( 1, 57, AXCO_KEY_RELEASE, 1.0f, 5.0f ); // space bar
  axco_end_alert();

  /*$1-  ---------------------------------------------------------------------*/
  t = timeGetTime();
  ticks = 0;

  return( AXE_TRUE );
}

/**
* each loop
*/
int loop() {
  if( (timeGetTime() - t) < 1000 ) {
    return( AXE_TRUE );
  }

  t = timeGetTime();
  ++ticks;

  AXE_INFO( "GETTING EVENTS ... %i", ticks );

  /*$1- Code here ------------------------------------------------------------*/
  axco_update();

  const axco_alert_fired*   alerts = axco_get_alerts_fired();

  for( register unsigned int i = 0; i < axco_get_num_alerts_fired(); ++i ) {
    AXE_INFO( "quietorr!" );
  }

  /*$1- Code here ------------------------------------------------------------*/
  if( ticks >= 5 ) {
    return( AXE_FALSE );
  } else {
    return( AXE_TRUE );
  }
}

/**
* on end app
*/
int end() {
  AXE_INFO( "Freeing Control" );
  axco_done();
  return( AXE_TRUE );
}

/**
* Simple code to test all functionality of the library
*/
__stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
  printf( "Axe 'control' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  // Start --------------------------------------------
  axwd_on_start( start );
  axwd_on_main_loop( loop );
  axwd_on_end( end );
  axwd_start_application( hInstance );
  axwd_end_application();

  // Finish --------------------------------------------
  printf( "\nAxe 'timer' library test FINISHED\n" );
  getchar();
  return( 1 );
}

/* $Id: axco_test.cpp,v 1.2 2004/07/21 22:08:52 doneval Exp $ */
