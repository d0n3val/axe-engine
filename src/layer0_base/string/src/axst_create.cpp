/**
* @file
* Axe 'string' code
*/
#include "axst_stdafx.h"

char axe_string:: tmp[AXST_MAX_STRING_SIZE];

/**
* constructor
*/
axe_string::axe_string()
{
  reset();
  reserve( AXST_DEFAULT_STRING_SIZE );
  clear();
}

/**
* destructor
*/
axe_string::~axe_string()
{
  destroy();
}

/**
* Destroy directly
*/
void axe_string::destroy()
{
  if( string != NULL )
  {
    AXE_RELEASE_ARRAY( string );
  }

  reset();
}

/**
* constructor from another axe_string
*/
axe_string::axe_string( const axe_string& str )
{
  reset();
  reserve( str.size );
  memcpy( string, str.string, str.size + 1 );
  size = str.size;
  checksum = str.checksum;
}

/**
* Constructor with minimum allocation space
*/
axe_string::axe_string( unsigned int required_space )
{
  reset();
  reserve( required_space );
  clear();
}

/**
* constructor from formatted char*
*/
axe_string::axe_string( const char* format, ... )
{
  AXE_ASSERT( format != NULL );

  reset();

  va_list ap;
  va_start( ap, format );

  int len = _vsnprintf_s( tmp, AXST_MAX_STRING_SIZE, AXST_MAX_STRING_SIZE, format, ap );
  va_end( ap );
  AXE_ASSERT( len != -1 );

  reserve( len );
  memcpy( string, tmp, len + 1 );
  size = len;
  calc_checksum();
}

/**
* constructor from formatted char* with max size
*/
axe_string::axe_string( unsigned int max_size, const char* format, ... )
{
  AXE_ASSERT( format != NULL );
  AXE_ASSERT( max_size < AXST_MAX_STRING_SIZE );

  reset();

  va_list ap;
  va_start( ap, format );
  _vsnprintf_s( tmp, AXST_MAX_STRING_SIZE, max_size, format, ap );
  va_end( ap );

  tmp[max_size] = '\0';

  int len = strlen( tmp );

  reserve( len );
  memcpy( string, tmp, len + 1 );
  size = len;
  calc_checksum();
}

/**
* create from another axe_string
*/
axe_string &axe_string::create( const axe_string& str )
{
  if( &str != this )
  {
    if( str.length() > 0 )
    {
      reserve( str.length() );
      memcpy( string, (const char*) str, str.length() + 1 );
      size = str.length();
      calc_checksum();
    }
    else
    {
      clear();
    }
  }

  return( *this );
}

/**
* create from formatted char*
*/
axe_string &axe_string::create( const char* format, ... )
{
  if( format != NULL )
  {
    va_list ap;
    va_start( ap, format );

    int len = _vsnprintf_s( tmp, AXST_MAX_STRING_SIZE, AXST_MAX_STRING_SIZE, format, ap );
    va_end( ap );
    AXE_ASSERT( len != -1 );

    reserve( len );
    memcpy( string, tmp, len + 1 );
    size = len;
    calc_checksum();
  }
  else
  {
    clear();
  }

  return( *this );
}

/**
* create from formatted char* with max size
*/
axe_string &axe_string::create( unsigned int max_size, const char* format, ... )
{
  AXE_ASSERT( max_size < AXST_MAX_STRING_SIZE );

  if( format != NULL )
  {
    va_list ap;
    va_start( ap, format );
    _vsnprintf_s( tmp, AXST_MAX_STRING_SIZE, max_size, format, ap );
    va_end( ap );

    tmp[max_size] = '\0';

    int len = strlen( tmp );

    reserve( len );
    memcpy( string, tmp, len + 1 );
    size = len;
    calc_checksum();
  }
  else
  {
    clear();
  }

  return( *this );
}

/* $Id: axst_create.cpp,v 1.3 2004/09/20 21:28:08 doneval Exp $ */
