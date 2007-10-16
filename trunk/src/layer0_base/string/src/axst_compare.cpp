/**
* @file
* Axe 'string' code to compare strings
*/
#include "axst_stdafx.h"

/**
* Compare (case sensitive) 2 axe_strings
*/
int axe_string::operator==( const axe_string& str ) const
{
  if( size != str.size )
  {
    return( AXE_FALSE );
  }

  if( checksum != str.checksum )
  {
    return( AXE_FALSE );
  }

  if( strcmp(string, str.string) != 0 )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/**
* Compare (case sensitive) a axe_string with a char*
*/
int axe_string::operator==( const char* str ) const
{
  AXE_ASSERT( str != NULL );
  if( size != strlen(str) )
  {
    return( AXE_FALSE );
  }

  if( strcmp(string, str) != 0 )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/**
* Compare (case sensitive) 2 axe_strings
*/
int axe_string::operator!=( const axe_string& str ) const
{
  return( !(*this == str) );
}

/**
* Compare (case sensitive) a axe_string with a char*
*/
int axe_string::operator!=( const char* str ) const
{
  return( !(*this == str) );
}

/**
* Compare (case INsensitive) 2 axe_strings
*/
int axe_string::compare_no_case( const axe_string& str ) const
{
  if( size != str.size )
  {
    return( AXE_FALSE );
  }

  if( _stricmp(string, str.string) != 0 )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/**
* Compare (case INsensitive) a axe_string with a char*
*/
int axe_string::compare_no_case( const char* str ) const
{
  AXE_ASSERT( str != NULL );
  if( size != strlen(str) )
  {
    return( AXE_FALSE );
  }

  if( _stricmp(string, str) != 0 )
  {
    return( AXE_FALSE );
  }

  return( AXE_TRUE );
}

/* $Id: axst_compare.cpp,v 1.1 2004/05/02 16:32:31 doneval Exp $ */
