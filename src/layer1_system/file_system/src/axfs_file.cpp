/**
* @file
* file class implementation
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      01 Apr 2004
*/
#include "axfs_stdafx.h"

#define TMP_NAME      "t_XXXXXX"
#define TMP_NAME_LEN  8

/**
* Constructor
*/
axfs_file::axfs_file( const char* file_name )
{
  size_t  len = strlen( file_name );

  if( len > 0 )
  {
    this->file_name.create( file_name );
  }
  else
  {
    // create a unique filename
    char  tmp[TMP_NAME_LEN + 5];
    strncpy_s( tmp, TMP_NAME_LEN, TMP_NAME, TMP_NAME_LEN );
    tmp[TMP_NAME_LEN] = 0;
    _mktemp_s( this->file_name, TMP_NAME_LEN + 5 );
    this->file_name.create( "%s.tmp", tmp );
  }

  // Make sure to create the file, even if it already exist
  int fp;
  int err = _sopen_s( &fp, file_name, _O_CREAT, _SH_DENYWR, _S_IREAD );
  AXE_ASSERT( err == 0 );
  _close( fp );

  data = NULL;
  fp = 0;
  size = 0;
}

/**
* Destructor
*/
axfs_file::~axfs_file()
{
  if( file_name != NULL )
  {
    delete file_name;
    file_name = NULL;
  }

  if( data != NULL )
  {
    free( data );
    data = NULL;
  }

  size = 0;
  fp = 0;
}

/**
* Checks if all is ok (file exists and we can read it)
*/
bool axfs_file::is_ok()
{
  int fp;
  int err = _sopen_s( &fp, file_name, _O_RDONLY | _O_BINARY, _SH_DENYWR, _S_IREAD );

  if( err != 0 )
  {
    return( false );
  }

  _close( fp );
  return( true );
}

/**
* returns a const pointer to the file data in memory
*/
const void *axfs_file::get_data( const bool use_cache )
{
  // check previously readed data
  if( true == use_cache && data != NULL )
  {
    return( data );
  }

  int fp;
  int err = _sopen_s( &fp, file_name, _O_RDONLY | _O_BINARY | _O_SEQUENTIAL, _SH_DENYWR, _S_IREAD );
  if( err != 0 )
  {
    return( NULL );
  }

  size = ( size_t ) _filelength( fp );

  if( data != NULL )
  {
    free( data );
    data = NULL;
    size = 0;
  }

  data = malloc( size );

  int res = _read( fp, data, (unsigned int) size );

  _close( fp );

  if( res <= 0 )
  {
    free( data );
    size = 0;
    return( NULL );
  }

  return( data );
}

/**
* returns the size of the file
*/
size_t axfs_file::get_size( const bool use_cache )
{
  if( use_cache == true && size > 0 )
  {
    return( size );
  }

  int fp;
  int err = _sopen_s( &fp, file_name, _O_RDONLY | _O_BINARY, _SH_DENYWR, _S_IREAD );
  if( err != 0 )
  {
    return( 0 );
  }

  size = ( size_t ) _filelength( fp );
  _close( fp );
  return( size );
}

/**
* changes entirely the data contained in the file
*/
bool axfs_file::set_data( const void* new_data, const size_t new_size )
{
  int fp;
  int err = _sopen_s( &fp, file_name, _O_TRUNC | _O_CREAT | _O_BINARY | _O_SEQUENTIAL, _SH_DENYWR, _S_IREAD );
  if( err != 0 )
  {
    return( NULL );
  }

  if( data != NULL )
  {
    free( data );
    data = NULL;
    size = 0;
  }

  int res = _write( fp, new_data, (unsigned int) new_size );
  _close( fp );

  if( res < 0 )
  {
    return( false );
  }

  data = malloc( new_size );
  memcpy( data, new_data, new_size );
  size = new_size;

  return( true );
}

/**
* Adds data in the position
*/
bool axfs_file::insert_data( const void* new_data, const size_t new_size, const size_t pos )
{
  // make sure we have the right data in this->data
  if( NULL == get_data() )
  {
    return( false );
  }

  size_t  p;

  if( pos > size )
  {
    p = size;
  }
  else
  {
    p = pos;
  }

  void*   all_data = malloc( new_size + size );
  memcpy( all_data, data, p );
  memcpy( all_data, new_data, new_size );
  memcpy( all_data, data, size - p );

  free( data );
  data = all_data;

  int fp;
  int err = _sopen_s( &fp, file_name, O_TRUNC | _O_CREAT | _O_BINARY | _O_SEQUENTIAL, _SH_DENYWR, _S_IREAD );
  if( err != 0 )
  {
    return( false );
  }

  int res = _write( fp, all_data, (unsigned int) new_size + size );
  _close( fp );

  if( res < 0 )
  {
    free( data );
    size = 0;
    return( false );
  }

  size = new_size + size;

  return( true );
}

/* $Id: axfs_file.cpp,v 1.2 2004/06/09 18:23:55 doneval Exp $ */
