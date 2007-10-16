/**
* @file
* Error Management code
*/
#include "axsi_stdafx.h"

extern _state state;	/// Global state of the library

/**
* Sets error notification data
*/
AXSI_API int axsi_set_error_data(const int error_num, char* file, long line) {
  state.last_error = error_num;
  strncpy(state.error_file, file, 128);
  state.error_line = line;
#ifdef _DEBUG
  /// @todo falta añadir file and line
  char title[256];
  _snprintf(title, 256, "Error at file %s line %ld", file, line);
  if(display_output(state.error_output, title, axsi_get_error_message(error_num)) == AXE_FALSE) {
    return(AXE_FALSE);
  }
#endif
  return(AXE_TRUE);
}

/**
* Gets last error notification data
*/
AXSI_API void axsi_get_error_data(int& error_num, char* file, long & line) {
  error_num = state.last_error;
  strncpy(file, state.error_file, 128);
  line = state.error_line;
}

/**
* Return only the error code
*/
AXSI_API const int axsi_get_error_number() {
  return(state.last_error);
}

/**
* Returns a message in english explaining an error code
* @see AXSI_LAST_ERROR
*/
AXSI_API const char* axsi_get_error_message( const int error_number ) {
  switch( error_number )
  {
  case 0:
    return( "No error" );

  case 1:
    return( "Function not yet implemented" );

  case 2:
    return( "Unknown error number" );

  case 3:
    return( "Bad argument/s" );

  case 4:
    return( "Could not start DirectX 9 Diagnostics" );

  case 5:
    return( "could not start COM interface with DirectX 9 Diagnostics" );
  }

  axsi_set_error(2);
  return( NULL );
}
