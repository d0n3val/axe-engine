/**
* @file
* Only basic lib functions
*/
#include "axlg_stdafx.h"

/** Global state of the library */
axlg_state  state;

#define AXLG_NUM_ERROR_MSG  1

/**
* List of error messages
" @see basic_error_messages
*/
const char*   error_messages[AXLG_NUM_ERROR_MSG] = { "Unknown error" };

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
AXLG_API unsigned int axlg_get( const int query_state ) {
  switch( query_state )
  {
    case AXLG_VERSION:
      return( state.lib_version );

    case AXLG_LIBRARY_ID:
      return( state.lib_id );

    case AXLG_LAST_ERROR:
      {
        int value = state.last_error;
        state.last_error = 0;
        return( value );
      }

    case AXLG_DEBUG_MODE:
      return( state.debug_mode );

    default:
      AXE_SET_ERROR( AXE_ERROR_MSG_COULD_NOT_GET_STATE );
      return( AXE_FALSE );
  }
}

/**
* Sets a library state
*/
AXLG_API unsigned int axlg_set( const int query_state, const unsigned int new_value ) {
  switch( query_state )
  {
    case AXLG_LAST_ERROR:
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
AXLG_API const char* axlg_get_error_message( const unsigned int error_number ) {
  int ok = AXE_IN_RANGE( error_number, 0, (AXE_NUM_BASIC_ERROR_MSG + AXLG_NUM_ERROR_MSG - 1) );
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
AXLG_API int axlg_set_error_callback( void (*error_callback) (int, const char*, long) ) {
  AXE_CHECK_DBG_ERROR( (NULL != error_callback), AXE_ERROR_MSG_BAD_ERROR_CALLBACK_FUNCTION );

  state.error_callback = error_callback;

  return( AXE_TRUE );
}

/* $Id: axlg_log.cpp,v 1.2 2004/07/27 22:42:47 doneval Exp $ */
