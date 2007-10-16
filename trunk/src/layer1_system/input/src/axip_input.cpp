/**
* @file
* Main library managment functions
*/
#include "axip_stdafx.h"

/** Global state of the library */
axip_state  state;

#define AXIP_NUM_ERROR_MSG  6

/**
* List of error messages
" @see basic_error_messages
*/
const char*   error_messages[AXIP_NUM_ERROR_MSG] =
{
  "Could not init DInput",                                          // 8
  "Could not init DInput devices",                                  // 9
  "Could not init DInput keyboard",                                 // 10
  "Could not init DInput mouse",                                    // 11
  "Could not init DInput joystick",                                 // 12
  "Could not acquire DInput device: other app has higher priority"  // 13
};

/**
* Main entry for the DLL
* Executed when the client do "loadlibrary"
*/
BOOL APIENTRY DllMain( HINSTANCE instance )
{
#ifdef _DEBUG
  // Initializes CRT Dbg
  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF );
  _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
  _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
  _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG );
#endif
  state.instance = instance;
  return( FALSE );
}

/**
* Returns a library state 
*/
AXIP_API unsigned int axip_get( const int query_state ) {
  switch( query_state )
  {
    case AXIP_VERSION:
      return( state.lib_version );

    case AXIP_LIBRARY_ID:
      return( state.lib_id );

    case AXIP_LAST_ERROR:
      {
        int value = state.last_error;
        state.last_error = 0;
        return( value );
      }

    case AXIP_DEBUG_MODE:
      return( state.debug_mode );

    default:
      AXE_SET_ERROR( AXE_ERROR_MSG_COULD_NOT_GET_STATE );
      return( AXE_FALSE );
  }
}

/**
* Sets a library state
*/
AXIP_API unsigned int axip_set( const int query_state, const unsigned int new_value ) {
  switch( query_state )
  {
    case AXIP_LAST_ERROR:
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
* @see AXIP_LAST_ERROR
* @see error_messages
*/
AXIP_API const char* axip_get_error_message( const unsigned int error_number ) {
  int ok = AXE_IN_RANGE( error_number, 0, (AXE_NUM_BASIC_ERROR_MSG + AXIP_NUM_ERROR_MSG - 1) );
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
AXIP_API int axip_set_error_callback( void (*error_callback) (int, const char*, long) ) {
  AXE_CHECK_DBG_ERROR( (NULL != error_callback), AXE_ERROR_MSG_BAD_ERROR_CALLBACK_FUNCTION );

  state.error_callback = error_callback;

  return( AXE_TRUE );
}

/* $Id: axip_input.cpp,v 1.2 2004/07/27 22:42:47 doneval Exp $ */
