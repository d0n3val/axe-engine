/**
* @file
* Functions regarding opnening / closing / flushing files
*/
#include "axlg_stdafx.h"

static char     priority_str[3][5] = { "INFO", "WARN", "ERRO" };
static char     tmp_string[4096];
static va_list  ap;

/**
* Comment
*/
AXLG_API int axlg_log( const char* format, ... )
{
  // check valid ref
  if( AXE_FALSE == state.ref_valid )
  {
    state.ref_valid = AXE_TRUE;
    return( AXE_FALSE );
  }

  // Construct the string from variable arguments
  va_start( ap, format );
  vsprintf_s( tmp_string, 4096, format, ap );
  va_end( ap );

  axe_string  str( tmp_string );

  // Filter the string if needed
  if( AXE_TRUE != state.filter.is_empty() )
  {
    if( AXE_TRUE != str.regex(state.filter) )
    {
      return( AXE_FALSE );
    }
  }

  // add references if exist
  if( AXE_TRUE == state.ref_exist )
  {
    str.create( "%s(%u): %s: %s", state.ref_file, state.ref_line, priority_str[state.ref_priority], tmp_string );
  }

  // Add carriage
  str += "\n\r";

  // Add the string to the list
  state.string_list.add( str );

  // Here check for different output managers (future: sockets, file, HTML, email, etc...)
  if( AXE_TRUE == state.output_to_console )
  {
    OutputDebugString( str );
  }

  return( AXE_TRUE );
}

/**
* Comment
*/
AXLG_API int axlg_log_ref( const char* file, const unsigned long line, axlg_priority priority )
{
  AXE_ASSERT( file != NULL );
  AXE_ASSERT( priority >= AXLG_INFO && priority <= AXLG_ERROR );

  if( priority < state.min_priority )
  {
    state.ref_valid = AXE_FALSE;
    return( AXE_FALSE );
  }

  // Set ref state
  int i;
  for( i = strlen(file) - 1; i >= 0; --i )
  {
    if( file[i] == '\\' )
    {
      ++i;
      break;
    }
  }

  strcpy_s( state.ref_file, 1024, &file[i] ); // filter ?
  state.ref_line = line;
  state.ref_priority = priority;
  state.ref_valid = AXE_TRUE;
  state.ref_exist = AXE_TRUE;

  return( AXE_TRUE );
}

/* $Id: axlg_add.cpp,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
