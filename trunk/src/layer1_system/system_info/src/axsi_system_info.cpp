/**
* @file
* Axe 'system_info' code
*/
#include "axsi_stdafx.h"

_state  state;

/// Global state of the library

/**
* Main entry for the DLL
* Executed when the client do "loadlibrary"
*/
BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved ) {
  if( ul_reason_for_call == DLL_PROCESS_ATTACH )
  {
#ifdef _DEBUG
    // Initializes CRT Dbg
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF );
    _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG );

    state.mode = AXSI_DEBUG;
    state.error_output = AXSI_OUTPUT_DEBUG;
    state.dump_output = AXSI_OUTPUT_DEBUG;
#else
    state.mode = AXSI_RELEASE;
    state.error_output = AXSI_NONE;
    state.dump_output = AXSI_NONE;
#endif
  }

#ifdef _DEBUG
  else if( ul_reason_for_call == DLL_PROCESS_DETACH ) {
    _CrtDumpMemoryLeaks();  // Not use automatic flag because there is a bug with multiple threads
  }

#endif
  return( TRUE );
}

/**
* Returns a library state
*/
AXSI_API int axsi_get_int( const int query_state ) {
  int error_number;

  switch( query_state )
  {
    case AXSI_VERSION:
      return( AXE_SYSTEM_INFO_VERSION );

    case AXSI_LIBRARY_ID:
      return( AXE_SYSTEM_INFO_LIBID );

    case AXSI_LAST_ERROR:
      error_number = state.last_error;
      state.last_error = 0;
      return( error_number );
  }

  return( AXE_FALSE );
}

/**
* Sets a library state
*/
AXSI_API int axsi_set_int( const int query_state, const int new_value ) {
  switch( query_state )
  {
    case AXSI_ERROR_OUTPUT:
      state.error_output = new_value;
      break;

    case AXSI_DUMP_OUTPUT:
      state.dump_output = new_value;
      break;

    default:
      return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/**
* Displays a string to specified output
*/
int display_output( const int output, const char* title, const char* data ) {
  switch( output )
  {
    case AXSI_OUTPUT_DEBUG:
      OutputDebugString( data );
      break;

    case AXSI_MESSAGE_BOX:
      MessageBox( NULL, data, title, MB_OK );
      break;

    case AXSI_DBG_MSG_BOX:
      if( MessageBox(NULL, data, title, MB_CANCELTRYCONTINUE | MB_ICONEXCLAMATION) == IDCANCEL ) {
        return( AXE_FALSE );
      }

      break;

    case AXSI_FILE:
      return( FALSE );
      break;

    case AXSI_BREAKPOINT:
      return( FALSE );
      break;
  }

  return( AXE_TRUE );
}

/* $Id: axsi_system_info.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
