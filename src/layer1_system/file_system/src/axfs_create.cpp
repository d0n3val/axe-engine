/**
* @file
* Creating and destroying memory mapped files
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      06 Apr 2004
*/
#include "axfs_stdafx.h"

/**
* Opens a file, copy all its data to mem and save it in linked list
*/
AXFS_API const AXE_ID axfs_create( const char* file_name, const int reload ) {
  AXE_CHECK_DBG_ERROR( (NULL != file_name), AXE_ERROR_MSG_BAD_ARGUMENTS );

  // search if we have already loaded this file
  axfs_file*  file = NULL;

  if( strlen(file_name) > 0 ) {
    AXE_LIST_FOR( state.file_list, axfs_file * ) {
      file = p_item->data;
      if( strcmp(file->file_name, file_name) == 0 ) {
        break;
      }
      file = NULL;
    }
  }

  if( file != NULL && reload != 0 ) {
    return( (const AXE_ID) file );
  }

  // since it does not exists, create it
  file = new axfs_file( file_name );

  return( (const AXE_ID) state.file_list.add(file) );
}

/**
* Closes a file and frees it's associated mem
*/
AXFS_API int axfs_destroy( const AXE_ID file_id, const int delete_file ) {
  axe_list_item<axfs_file *>*   item = ( axe_list_item < axfs_file * > * ) file_id;
#ifdef _DEBUG
  bool                          ok = state.file_list.search( item );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  if( delete_file == AXE_TRUE ) {
    axfs_delete_file( item->data->file_name );
  }

  state.file_list.del( item );

  return( AXE_TRUE );
}

/* $Id: axfs_create.cpp,v 1.4 2004/07/27 21:19:26 ilgenio Exp $ */
