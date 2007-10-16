/**
* @file
* Axe 'events' test code
* @see axe_events.h
*/
#include "axev_test.h"

#define AXEV_NO_AUTOLINK
#include "axe_events.h"

/// Version of this test code
#define AXE_EVENTS_TEST_VERSION 1

// Use proper library --------
#ifdef _DEBUG
  #pragma comment( lib, "../../../output_debug/lib/axe_events.lib" )
#else
  #pragma comment( lib, "../../../output_release/lib/axe_events.lib" )
#endif

/**
* Checks for the current 'error' state of the library
*/
void error( int num, const char* file, long line ) {
  printf( "\n\n\n*** ERROR in %s(%u): %s\n", file, line, axev_get_error_message(num) );
  getchar();
}

/**
* Checks if this code and the lib have the same version
*/
int check_versions() {
  printf( "\nGetting lib version ... " );

  int lib_version = axev_get( AXEV_VERSION );

  if( lib_version != AXE_EVENTS_TEST_VERSION ) {
    printf(
      "This test program and the library versions differ! Lib:%d Test:%d\n",
      lib_version,
      AXE_EVENTS_TEST_VERSION );
    getchar();
    return( 0 );
  }

  printf( "Library Version: %d - This testing program: %d\n\n", lib_version, AXE_EVENTS_TEST_VERSION );

  return( 1 );
}

/**
* callback
*/
void key_callback( AXE_ID event_id, void* data ) {
  printf( "Event %d called -> %s\n", event_id, (char*) data );
}

/**
* Simple code to test all functionality of the library
*/
int main() {
  printf( "Axe 'events' library test STARTED\n" );

  // Check versions ------------------------------------
  if( check_versions() == 0 ) {
    return( 0 );
  }

  // Start ---------------------------------------------
  AXE_ID  event_id;

  event_id = axev_create_event();
  axev_add_event_callback( event_id, key_callback );

  axev_call_event( event_id, "hola1", 1.0f );
  axev_call_event( event_id, "hola2", 1.0f );
  axev_call_event( event_id, "hola3", 1.0f );
  axev_call_event( event_id, "hola4", 2.0f );
  axev_call_event( event_id, "hola5", -5.0f );
  axev_call_event( event_id, "hola6", 3.0f );
  axev_call_event( event_id, "hola7", 4.0f );
  axev_call_event( event_id, "hola8", 5.0f );

  while( !GetAsyncKeyState(VK_RETURN) ) {
    axev_update();
  }

  // Finish --------------------------------------------
  printf( "\nAxe 'events' library test FINISHED\n" );

  return( 1 );
}

/* $Id: axev_test.cpp,v 1.1 2004/07/27 22:42:49 doneval Exp $ */
