/**
* @file
* Axe 'string' code to add strings to strings
*/
#include "axst_stdafx.h"

/**
* copy from another axe_string
*/
axe_string &axe_string::operator=( const axe_string& str )
{
  create( "%s", str.get_str() );
  return( *this );
}

/**
* copy from char*
*/
axe_string &axe_string::operator=( const char* str )
{
  if( str != NULL )
  {
    create( "%s", str );
  }
  else
  {
    clear();
  }

  return( *this );
}

/**
* Concat another axe_string
*/
axe_string axe_string::operator+( const axe_string& str ) const
{
  axe_string  str1( *this );
  return( str1 += str );
}

/**
* Concat another char*
*/
axe_string axe_string::operator+( const char* str ) const
{
  axe_string  str1( *this );
  return( str1 += str );
}

/**
* Concat char* + string
*/
AXST_API axe_string operator+( const char* str1, const axe_string& str2 )
{
  axe_string  str( "%s%s", str1, str2 );
  return( str );
}

/**
* Concat directle from an axe_string
*/
axe_string &axe_string::operator+=( const axe_string& str )
{
  check_size( str.size + 1 );
  memcpy( (string + size), str.string, str.size + 1 );
  size += str.size;
  calc_checksum();
  return( *this );
}

/**
* copy from another axe_string
*/
axe_string &axe_string::operator+=( const char* str )
{
  if( str != NULL )
  {
    unsigned int  len = (unsigned int) strlen( str );
    check_size( len + 1 );
    memcpy( (string + size), str, len + 1 );
    size += len;
    calc_checksum();
  }

  return( *this );
}

/**
* Concat a single char
*/
axe_string &axe_string::operator+=( const char ch )
{
  check_size( 1 );
  string[size] = ch;
  string[size + 1] = 0;
  size += 1;
  calc_checksum();

  return( *this );
}

/**
* Add formatted text
*/
axe_string &axe_string::add( const char* format, ... )
{
  AXE_ASSERT( format != NULL );

  va_list ap;
  va_start( ap, format );

  int len = _vsnprintf_s( tmp, AXST_MAX_STRING_SIZE, AXST_MAX_STRING_SIZE, format, ap );
  va_end( ap );

  AXE_ASSERT( len != -1 );

  check_size( len + 1 );
  memcpy( (string + size), tmp, len + 1 );
  size += len;
  calc_checksum();

  return( *this );
}

/**
* copy from another CString
*/
axe_string &axe_string::prepend( const char* format, ... )
{
  AXE_ASSERT( format != NULL );

  va_list ap;
  va_start( ap, format );

  int len = _vsnprintf_s( tmp, AXST_MAX_STRING_SIZE, AXST_MAX_STRING_SIZE, format, ap );
  va_end( ap );

  AXE_ASSERT( len != -1 );

  check_size( len + 1 );
  memcpy( (string + len), string, size + 1 );
  memcpy( string, tmp, len );
  size += len;
  calc_checksum();

  return( *this );
}

/* $Id: axst_add.cpp,v 1.2 2004/06/09 18:23:54 doneval Exp $ */
