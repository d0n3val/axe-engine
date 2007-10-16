/**
* @file
* Axe 'input' test code
* @see axe_input.h
*/
#include "axip_test.h"

#define AXIP_NO_AUTOLINK
#include "../src/axe_input.h"
#define AXWD_NO_AUTOLINK
#include "../../windows/src/axe_windows.h"
#define AXLG_NO_AUTOLINK
#include "../../log/src/axe_log.h"

/// Version of this test code
#define AXE_INPUT_TEST_VERSION  1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_input.lib" )
  #pragma comment( lib, "../../../output_debug/lib/axe_windows.lib" )
  #pragma comment( lib, "../../../output_debug/lib/axe_log.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_input.lib" )
  #pragma comment( lib, "../../../output_release/lib/axe_windows.lib" )
  #pragma comment( lib, "../../../output_release/lib/axe_log.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line ) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axip_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axip_get( AXIP_VERSION );

  if( lib_version != AXE_INPUT_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_INPUT_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_INPUT_TEST_VERSION );

  return( 1 );
}

DWORD t;
int   ticks;

/**
* On start app
*/
int start() {
  win_info  info = axwd_get_windows_info();

  AXE_INFO( "Init DInput" );
  axip_init( info.window, info.instance );

  int num_dev = axip_get_num_devices();
  for( register int i = 0; i < num_dev; ++i ) {
    axip_set_active( i, AXE_TRUE );

    axip_device_info  dev;
    axip_get_device( i, &dev );
    AXE_INFO( "Device found: %s", dev.name );
  }

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
  const axip_event* events = NULL;

  events = axip_get_events();

  if ( events != NULL ) {
    for( register unsigned int i = 0; i < axip_get_num_events(); ++i ) {
      AXE_INFO( "EVENT: device(%i) type(%i) value(%i) time(%u)", events[i].device, events[i].type, events[i].value, events[i].time );	
    }
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
  AXE_INFO( "Freeing DInput" );
  axip_done();
  return( AXE_TRUE );
}

/**
* Simple code to test all functionality of the library
*/
__stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {
  printf( "Axe 'input' library test STARTED\n" );

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

/* $Id: axip_test.cpp,v 1.2 2004/06/11 20:14:29 doneval Exp $ */
