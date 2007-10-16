/**
* @file
* Util functions for file managment
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      08 Apr 2004
*/
#include "axfs_stdafx.h"

/**
* Check if certain file exists
*/
AXFS_API int axfs_file_exists( const char* file_name )
{
  AXE_CHECK_DBG_ERROR( (NULL != file_name), AXE_ERROR_MSG_BAD_ARGUMENTS );

  int fp;
  int err = _sopen_s( &fp, file_name, _O_RDONLY | _O_BINARY, _SH_DENYWR, _S_IREAD );
  if( err != 0 )
  {
    return( AXE_FALSE );
  }

  _close( fp );
  return( AXE_TRUE );
}

/**
* Returns the size of the file
*/
AXFS_API unsigned int axfs_file_size( const char* file_name )
{
  AXE_CHECK_DBG_ERROR( (NULL != file_name), AXE_ERROR_MSG_BAD_ARGUMENTS );

  int fp;
  int err = _sopen_s( &fp, file_name, _O_RDONLY | _O_BINARY, _SH_DENYWR, _S_IREAD );
  AXE_CHECK_ERROR( (err != 0), 8 );

  unsigned int  size = _filelength( fp );

  _close( fp );
  return( size );
}

/**
* Unlinks file
*/
AXFS_API int axfs_delete_file( const char* file_name )
{
  AXE_CHECK_DBG_ERROR( (NULL != file_name), AXE_ERROR_MSG_BAD_ARGUMENTS );

  AXE_CHECK_ERROR( (0 == _unlink(file_name)), 9 );

  return( AXE_TRUE );
}

/**
* Renames a file
*/
AXFS_API int axfs_rename_file( const char* file_name, const char* new_file_name )
{
  AXE_CHECK_DBG_ERROR( (NULL != file_name && NULL != new_file_name), AXE_ERROR_MSG_BAD_ARGUMENTS );

  AXE_CHECK_ERROR( (0 == rename(file_name, new_file_name)), 10 );

  return( AXE_TRUE );
}

/* $Id: axfs_util.cpp,v 1.1 2004/05/02 16:32:31 doneval Exp $ */
