/**
* @file
* Only basic lib functions
*/
#include "axwd_stdafx.h"

/** Global state of the library */
axwd_state  state;

#define AXWD_NUM_ERROR_MSG  13

/**
* List of error messages
" @see basic_error_messages
*/
const char*   error_messages[AXWD_NUM_ERROR_MSG] =
{
  "An 'on_loop()' function is needed to start",                 // 8
  "Application already started",                                // 9
  "Could not register window class",                            // 10
  "Error trying to adjust window size with AdjustWindowRect()", // 11
  "Could not set the window creation hook",                     // 12
  "Could not create window",                                    // 13
  "Cannot end application since it did not start",              // 14
  "Changing resolution: could not enum display settings",       // 15
  "Display Mode Not Compatible",                                // 16
  "Could not change window position and size",                  // 17
  "Could not change window style",                              // 18
  "Could not use device context",                               // 19
  "Could not create pixel format",                              // 20 
};

/**
* Main entry for the DLL
* Executed when the client do "loadlibrary"
*/
BOOL APIENTRY DllMain()
{
#ifdef _DEBUG
  // Initializes CRT Dbg
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );
  _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
  _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG );
#endif
  return( TRUE );
}

/**
* Returns a library state
*/
AXWD_API unsigned int axwd_get( const int query_state ) {
  int error_number;

  switch( query_state )
  {
    case AXWD_VERSION:
      return( state.lib_version );

    case AXWD_LIBRARY_ID:
      return( state.lib_id );

    case AXWD_LAST_ERROR:
      {
        error_number = state.last_error;
        state.last_error = 0;
        return( error_number );
      }

    case AXWD_DEBUG_MODE:
      return( state.debug_mode );

    case AXWD_FULLSCREEN:
      return( state.fullscreen );

    case AXWD_MAXIMIZED:
      return( state.maximized );

    case AXWD_MINIMIZED:
      return( state.minimized );

    case AXWD_PAUSED:
      return( state.paused );

    case AXWD_ENDING:
      return( state.exiting );

    case AXWD_STARTED:
      return( state.started );

    default:
      AXE_SET_ERROR( AXE_ERROR_MSG_COULD_NOT_GET_STATE );
      return( AXE_FALSE );
  }
}

/**
* Sets a library state
*/
AXWD_API unsigned int axwd_set( const int query_state, const unsigned int new_value ) {
  switch( query_state ) {
    case AXWD_FULLSCREEN:
      if( new_value == 0 ) {
        axwd_change_to_windowed();
      } else {
        axwd_change_to_fullscreen();
      }

      break;

    case AXWD_PAUSED:
      state.set_pause( AXE_TRUE );
      break;

    case AXWD_ENDING:
      state.exiting = new_value;
      break;

    case AXWD_LAST_ERROR:
      state.last_error = new_value;
      break;

    default:
      AXE_SET_ERROR( AXE_ERROR_MSG_COULD_NOT_SET_STATE );
      return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/**
* Returns a message in english explaining an error code
* @see AXLG_LAST_ERROR
* @see error_messages
*/
AXWD_API const char* axwd_get_error_message( const unsigned int error_number ) {
  int ok = AXE_IN_RANGE( error_number, 0, (AXE_NUM_BASIC_ERROR_MSG + AXWD_NUM_ERROR_MSG - 1) );
  AXE_CHECK_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ERROR_NUMBER );

  if( error_number < AXE_NUM_BASIC_ERROR_MSG ) {
    return( basic_error_messages[error_number] );
  } else {
    return( error_messages[error_number - AXE_NUM_BASIC_ERROR_MSG] );
  }
}

/**
* Sets callback function to call in case of errors
*/
AXWD_API int axwd_set_error_callback( void (*error_callback) (int, const char*, long) ) {
  AXE_CHECK_DBG_ERROR( (NULL != error_callback), AXE_ERROR_MSG_BAD_ERROR_CALLBACK_FUNCTION );

  state.error_callback = error_callback;

  return( AXE_TRUE );
}

/* $Id: axwd_windows.cpp,v 1.2 2004/07/27 22:42:48 doneval Exp $ */
