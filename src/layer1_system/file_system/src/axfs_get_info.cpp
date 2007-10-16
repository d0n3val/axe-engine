/**
* @file
* Get info about already opened files
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      06 Apr 2004
*/
#include "axfs_stdafx.h"

/**
* Gets the file name asociated with the AXE_ID
*/
AXFS_API const char* axfs_get_name( const AXE_ID file_id )
{
#ifdef _DEBUG
  bool  ok = state.file_list.search( (axe_list_item < axfs_file * > *) file_id );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  return( ((axe_list_item < axfs_file * > *) file_id)->data->file_name );
}

/**
* Gets the size of the memory allocated for a file
*/
AXFS_API size_t axfs_get_size( const AXE_ID file_id )
{
#ifdef _DEBUG
  bool  ok = state.file_list.search( (axe_list_item < axfs_file * > *) file_id);
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif
  return( ((axe_list_item < axfs_file * > *) file_id)->data->get_size() );
}

/* $Id: axfs_get_info.cpp,v 1.2 2004/07/27 21:19:26 ilgenio Exp $ */
