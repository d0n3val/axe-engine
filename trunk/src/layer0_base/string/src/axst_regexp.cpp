/**
* @file
* Front-end to the re_lib library
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      28 Mar 2004
*/
#include "axst_stdafx.h"
#include "re_lib/regexp.h"

/**
* Search a match with a regular expression
*/
int axe_string::regex( const char* expr, unsigned int offset, axe_string::regex_result* result ) const
{
  AXE_ASSERT( expr != NULL );

  regexp*   r;
  r = regcomp( expr );

  if( r == NULL )
  {
    return( AXE_FALSE );
  }

  if( regexec(r, string + offset) == 0 )
  {
    AXE_RELEASE_ARRAY( r );
    return( AXE_FALSE );
  }

  if( result != NULL )
  {
    convert_regex_result( r, result, offset );
  }

  AXE_RELEASE_ARRAY( r );

  return( AXE_TRUE );
}

/**
* Replace using regular expressions
*/
int axe_string::regex_replace( const char*                 expr,
                               const char*                 sub_string,
                               unsigned int                offset,
                               axe_string::regex_result*   result )
{
  AXE_ASSERT( expr != NULL );
  AXE_ASSERT( sub_string != NULL );

  regexp*   r;
  r = regcomp( expr );

  if( r == NULL )
  {
    return( AXE_FALSE );
  }

  if( regexec(r, string + offset) == 0 )
  {
    AXE_RELEASE_ARRAY( r );
    return( AXE_FALSE );
  }

  if( result != NULL )
  {
    convert_regex_result( r, result, offset );
  }

  regsub( r, sub_string, tmp, AXST_MAX_STRING_SIZE );
  create( tmp );

  AXE_RELEASE_ARRAY( r );

  return( AXE_TRUE );
}

/**
* Simple replace
*/
int axe_string::replace( const char* word_to_replace, const char* format, ... )
{
  AXE_ASSERT( word_to_replace != NULL );
  AXE_ASSERT( format != NULL );

  static char tmp2[AXST_MAX_STRING_SIZE];

  va_list     ap;
  va_start( ap, format );

  int len = _vsnprintf_s( tmp2, AXST_MAX_STRING_SIZE, AXST_MAX_STRING_SIZE, format, ap );
  va_end( ap );
  AXE_ASSERT( len != -1 );

  //regex("(%s)", 0, &r);
  axe_string  csReplace( "^(.*)(%s)(.*)$", word_to_replace );

  /*$1- Sometimes, user needs to specificy the brackets ----------------------*/
  if( word_to_replace[0] == '^' )
  {
    csReplace.create( word_to_replace );
  }

  axe_string    csSubString( "\\1%s\\3\\4\\5\\6\\7\\8\\9", tmp2 );

  int           count = 0;
  unsigned int  offset = 0;
  regex_result  res;

  while( regex_replace(csReplace, csSubString, offset, &res) == AXE_TRUE )
  {
    //offset += res.start[1] + len;
    ++count;
  }

  return( count );
}

/**
* Replace using regular expressions
*/
int axe_string::regex_replaceII( const char*     expr,
                                 const char*     sub_string,
                                 unsigned int    offset,
                                 unsigned int*   pIntNextReplace )
{
  int bRet = AXE_TRUE;
  AXE_ASSERT( expr != NULL );
  AXE_ASSERT( sub_string != NULL );

  regexp*   r;
  r = regcomp( expr );

  if( r == NULL )
  {
    return( AXE_FALSE );
  }

  if( regexec(r, string + offset) == 0 )
  {
    AXE_RELEASE_ARRAY( r );
    return( AXE_FALSE );
  }

  regsub( r, sub_string, tmp, AXST_MAX_STRING_SIZE );

  int iLenTextoQueReemplaza = strlen( tmp );
  int iLenTextoSustituido = r->endp[0] - r->startp[0];
  int iLenTextoInicio = r->startp[0] - string;
  int iLenTextoFin = size - ( r->endp[0] - string );

  if( iLenTextoSustituido )
  {
    int iLenResultado = iLenTextoInicio + iLenTextoFin +
      ( iLenTextoQueReemplaza > iLenTextoSustituido ? iLenTextoQueReemplaza : iLenTextoSustituido );
    if( iLenResultado )
    {
      char*   pszNew = new char[iLenResultado + 1];
      char*   pszNewAux = pszNew;

      if( iLenTextoInicio )
      {
        memcpy( pszNewAux, string, iLenTextoInicio );
        pszNewAux += iLenTextoInicio;
      }

      strcpy_s( pszNewAux, iLenResultado + 1, tmp );
      pszNewAux += iLenTextoQueReemplaza;

      if( iLenTextoFin )
      {
        memcpy( pszNewAux, r->endp[0], iLenTextoFin );
        pszNewAux += iLenTextoFin;
      }

      *pszNewAux = '\0';

      if( pIntNextReplace )
      {
        *pIntNextReplace = iLenTextoInicio + iLenTextoQueReemplaza;
      }

      create( pszNew );
      AXE_RELEASE_ARRAY( pszNew );
    }
    else
    {
      bRet = AXE_FALSE;
    }
  }
  else
  {
    create( "" );
  }

  AXE_RELEASE_ARRAY( r );

  return( AXE_TRUE );
}

int axe_string::replaceII( const char* word_to_replace, const char* format, ... )
{
  AXE_ASSERT( word_to_replace != NULL );
  AXE_ASSERT( format != NULL );

  static char tmp2[AXST_MAX_STRING_SIZE];

  va_list     ap;
  va_start( ap, format );

  int len = _vsnprintf_s( tmp2, AXST_MAX_STRING_SIZE, AXST_MAX_STRING_SIZE, format, ap );
  va_end( ap );
  AXE_ASSERT( len != -1 );

  int bSoloUnaVuelta = 0;

  if( *word_to_replace == '^' )
  {
    bSoloUnaVuelta = AXE_TRUE;
  }

  unsigned  iOffset = 0;
  unsigned  iNextReplace = 0;
  int       count = 0;

  if( bSoloUnaVuelta )
  {
    regex_replaceII( word_to_replace, tmp2 );
  }
  else
  {
    while( regex_replaceII(word_to_replace, tmp2, iOffset, &iNextReplace) == AXE_TRUE )
    {
      iOffset = iNextReplace;
      ++count;
    }
  }

  return( count );
}

/**
* Create a axe_string::regex_result from an regexp*
*/
void axe_string::convert_regex_result( regexp* r, axe_string::regex_result* result, unsigned int offset ) const
{
  AXE_ASSERT( result != NULL );
  AXE_ASSERT( r != NULL );

  memset( result, 0, sizeof(axe_string::regex_result) );

  int iInsertados = 0;
  for( unsigned int i = 1; i < NSUBEXP; ++i )
  {
    if( r->startp[i] == NULL )
    {
      break;
    }

    result->start[iInsertados] = r->startp[i] - ( string + offset );
    result->end[iInsertados] = r->endp[i] - ( string + offset );
    result->len[iInsertados] = r->endp[i] - r->startp[i];

    if( result->len[i - 1] > 0 )
    {
      ++iInsertados;
    }
  }

  result->size = iInsertados;
}

/* $Id: axst_regexp.cpp,v 1.1 2004/05/02 16:32:31 doneval Exp $ */
