/**
* @file
* Utils fpor the string class
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      28 Mar 2004
*/
#include "axst_stdafx.h"

/**
* Update calculate members. Used when other processes modify the data directly.
*/
void axe_string::update()
{
  size = strlen( string );
  calc_checksum();
}

/**
* Make sure that "alloc space" is allocated
*/
void axe_string::reserve( const unsigned int required_space )
{
  if( (required_space + 1) <= max_size )
  {
    return;
  }

  max_size = ( required_space + 1 );
  alloc();
}

/**
* check for proper size
*/
unsigned int axe_string::get_reserved() const
{
  return( max_size );
}

/**
* check for proper size
*/
void axe_string::check_size( const unsigned int required_space )
{
  if( (size + required_space + 1) < max_size )
  {
    return;
  }

  if( required_space < AXST_DEFAULT_STRING_SIZE )
  {
    max_size += AXST_DEFAULT_STRING_SIZE;
  }
  else
  {
    max_size += required_space + AXST_DEFAULT_STRING_SIZE;
  }

  alloc();
}

/**
* check for proper size
*/
void axe_string::alloc()
{
  string = new char[max_size];

  /*
  char*   tmp = NEW_ARRAY (char, max_size);

  // Si string != NULL es que tenemos que hacer un realloc
  if( string != NULL )
  {
    memcpy( tmp, string, strlen(string) + 1 );
    AXE_DELETE_ARRAY( string );
  }

  string = tmp;
  */
}

/**
* calculate my checksum
*/
void axe_string::calc_checksum()
{
  checksum = 0;

  if( get_str() )
  {
    for( register unsigned int i = 0; i < size; ++i )
    {
      checksum ^= ( (i & 1) == 0 ) ? ( (checksum << 7) ^ string[i] ^ (checksum >> 3) ) : ( ~((checksum << 11) ^ string[i] ^ (checksum >> 5)) );
    }
  }

  checksum &= 0x7FFFFFFF;
}

/**
* Reset alloc values
*/
void axe_string::reset()
{
  size = max_size = checksum = 0;
  string = NULL;
}

/**
* clean axe_string
*/
void axe_string::clear()
{
  if( get_str() )
  {
    memset( string, 0, max_size );
  }

  size = 0;
}

/**
* get a character from the axe_string (const)
*/
const char axe_string::operator [] (int index) const
{
  if( index < 0 || index > (int) size )
  {
    return( 0 );
  }

  return( string[index] );
}

/**
* get a character from the axe_string
*/
char *axe_string::operator  [] (int index)
{
  if( get_str() )
  {
    AXE_ASSERT( index >= 0 && index < (int) max_size );
    return( &string[index] );
  }
  else
  {
    return( 0 );
  }
}

/**
* Cuts the string
*/
void axe_string::cut( unsigned int start, unsigned int end )
{
  if( get_str() )
  {
    start = AXE_MIN( start, size );
    end = ( end == 0 ) ? size : AXE_MIN( end, size );

    AXE_ASSERT( start <= end );

    int s = end - start;

    if( start > 0 )
    {
      memmove( string, &string[start], s );
    }

    string[s] = '\0';
    update();
  }
}

/**
* Paste a substring into buffer
*/
unsigned int axe_string::sub_string( unsigned int start, unsigned int end, char* buffer ) const
{
  if( get_str() )
  {
    AXE_ASSERT( buffer != NULL );

    start = AXE_MIN( start, size );
    end = ( end == 0 ) ? size : AXE_MIN( end, size );

    AXE_ASSERT( start <= end );

    int s = end - start;

    memcpy( buffer, &string[start], s );
    buffer[s] = '\0';

    return( end - start );
  }
  else
  {
    buffer[0] = '\0';
    return( 0 );
  }
}

/**
* Paste a substring into buffer
*/
unsigned int axe_string::sub_string( unsigned int start, unsigned int end, axe_string& buffer ) const
{
  if( get_str() )
  {
    start = AXE_MIN( start, size );
    end = ( end == 0 ) ? size : AXE_MIN( end, size );

    AXE_ASSERT( start <= end );

    int s = end - start;

    buffer.create( s, "%s", &(string[start]) );

    return( end - start );
  }
  else
  {
    return( 0 );
  }
}

/**
* Convert the string to upper case
*/
axe_string &axe_string::to_upper_case()
{
  if( get_str() )
  {
    for( register unsigned int i = 0; i < size; ++i )
    {
      string[i] = toupper( string[i] );
    }

    calc_checksum();
  }

  return( *this );
}

/**
* Convert the string to lower case
*/
axe_string &axe_string::to_lower_case()
{
  if( get_str() )
  {
    for( register unsigned int i = 0; i < size; ++i )
    {
      string[i] = tolower( string[i] );
    }

    calc_checksum();
  }

  return( *this );
}

/**
* Convert all to lower case but the first char
*/
axe_string &axe_string::capitalize()
{
  if( get_str() )
  {
    for( register unsigned int i = 0; i < size; ++i )
    {
      if( i == 0 )
      {
        string[i] = toupper( string[i] );
      }
      else
      {
        string[i] = tolower( string[i] );
      }
    }

    calc_checksum();
  }

  return( *this );
}

/**
* Convert the string to upper case
*/
axe_string &axe_string::capitalize_after_underscores()
{
  if( get_str() )
  {
    int bNextUpper = AXE_TRUE;
    int iCopy = 0;

    for( register unsigned int i = 0; i < size; ++i )
    {
      if( string[i] == '_' )
      {
        bNextUpper = AXE_TRUE;
      }
      else if( bNextUpper )
      {
        string[iCopy] = toupper( string[i] );
        iCopy++;
        bNextUpper = AXE_FALSE;
      }
      else
      {
        string[iCopy] = tolower( string[i] );
        iCopy++;
      }
    }

    string[iCopy] = '\0';
    update();
  }

  return( *this );
}

/**
* Cut spaces (or other char) from left/right of the string
*/
axe_string &axe_string::trim( int left, int right, char ch )
{
  if( get_str() )
  {
    unsigned int  pos_left = find_char( ch, AXE_FALSE );
    unsigned int  pos_right = find_char( ch, AXE_TRUE );

    if( left )
    {
      if( pos_left > 0 )
      {
        memcpy( string, &string[pos_left], size - pos_left );
        string[size - pos_left] = 0;
      }
    }

    if( right )
    {
      if( pos_right < size - 1 )
      {
        string[pos_right - pos_left + 1] = '\0';
      }
    }

    update();
  }

  return( *this );
}

/**
* Locates the first or last entry of a char
*/
unsigned int axe_string::find_char( char ch, int from_last )
{
  unsigned int  i = 0;

  if( get_str() )
  {
    if( from_last == AXE_TRUE )
    {
      i = size - 1;
    }

    while( i < size && i >= 0 )
    {
      if( string[i] != ch )
      {
        return( i );
      }

      if( from_last == AXE_FALSE )
      {
        ++i;
      }
      else
      {
        --i;
      }
    }
  }

  return( i );
}

/**
* Count all entries of certain char
*/
unsigned int axe_string::count_char( char ch )
{
  unsigned int  iRet = 0;

  if( get_str() )
  {
    for( unsigned int u = 0; u < length(); ++u )
    {
      if( string[u] == ch )
      {
        iRet++;
      }
    }
  }

  return( iRet );
}

/**
* Returns a token from a list separated with "separator" ... like "a:b:dsadf:asd:12:token"
*/
int axe_string::get_token( const char* separator, unsigned int num_token, axe_string& buffer ) const
{
  AXE_ASSERT( separator != NULL );

  if( get_str() )
  {
    unsigned int  len = strlen( separator );

    if( size < len )
    {
      return( AXE_FALSE );
    }

    unsigned int          offset = 0;
    unsigned int          count = 0;
    regex_result  res;
    axe_string    csSeparator( "(%s)", separator );

    /*$1- Search for tokens --------------------------------------------------*/
    while( regex(csSeparator, offset, &res) == AXE_TRUE )
    {
      if( count == num_token )
      {
        sub_string( offset, offset + res.start[0], buffer );
        return( AXE_TRUE );
      }

      offset += res.end[0];
      ++count;
    }

    /*$1- Return the last token ----------------------------------------------*/
    if( offset < size && count == num_token )
    {
      sub_string( offset, size, buffer );
      return( AXE_TRUE );
    }
  }

  return( AXE_FALSE );
}

/**
* Remove a char
*/
axe_string &axe_string::delete_char( char ch )
{
  if( get_str() )
  {
    int bEliminarChar = AXE_TRUE;
    int iCopy = 0;

    for( register unsigned int i = 0; i < size; ++i )
    {
      if( string[i] != ch )
      {
        string[iCopy] = ( string[i] );
        iCopy++;
      }
    }

    string[iCopy] = '\0';
    update();
  }

  return( *this );
}

/* $Id: axst_util.cpp,v 1.3 2004/09/20 21:28:08 doneval Exp $ */
