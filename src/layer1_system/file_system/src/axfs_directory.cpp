/**
* @file
* Directory management functions
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      08 Apr 2004
*/
#include "axfs_stdafx.h"

/**
* Get current directory
*/
AXFS_API const char* axfs_get_current_dir() {
  AXE_CHECK_ERROR( (NULL != _getcwd(state.current_dir, _MAX_PATH)), 12 );

  return( (const char*) state.current_dir );
}

/**
* Change current directory
*/
AXFS_API int axfs_change_dir( const char* new_dir ) {
  AXE_CHECK_ERROR( (0 == _chdir(new_dir)), 13 );

  return( AXE_TRUE );
}

/**
* Creates a new directory
*/
AXFS_API int axfs_create_dir( const char* new_dir ) {
  AXE_CHECK_ERROR( (0 == _mkdir(new_dir)), 14 );

  return( AXE_TRUE );
}

/**
* Removes an empty directory
*/
AXFS_API int axfs_remove_dir( const char* dir ) {
  AXE_CHECK_ERROR( (0 == _rmdir(dir)), 15 );

  return( AXE_TRUE );
}

/* $Id: axfs_directory.cpp,v 1.1 2004/05/02 16:32:31 doneval Exp $ */
