/**
* @file
* Read / Write data to files
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      06 Apr 2004
*/
#include "axfs_stdafx.h"

/**
* Gets a data asociated with an AXE_ID
*/
AXFS_API const void* axfs_get_data( const AXE_ID file_id, const int reload )
{
#ifdef _DEBUG
  bool  ok = state.file_list.search( (axe_list_item < axfs_file * > *) file_id );
  AXE_CHECK_DBG_ERROR( ok, 9 );
#endif

  axfs_file*  file = ( (axe_list_item < axfs_file * > *) file_id )->data;

  if( reload == 0 ) {
    return( file->get_data(false) );
  }

  return( file->get_data(true) );
}

/**
* Sets te data of the file. The effcts are inmediate
*/
AXFS_API int axfs_set_data( const AXE_ID file_id, const void* data, const size_t size )
{
#ifdef _DEBUG
  AXE_CHECK_DBG_ERROR( (NULL != data && 0 < size), AXE_ERROR_MSG_BAD_ARGUMENTS );
  bool  ok = state.file_list.search( (axe_list_item < axfs_file * > *) file_id );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif

  axfs_file*  file = ( (axe_list_item < axfs_file * > *) file_id )->data;

  file->set_data( data, size );

  return( AXE_TRUE );
}

/**
* Insert data in a certain position of the file. Effects are inmediate
*/
AXFS_API int axfs_insert_data( const AXE_ID file_id, const void* data, const size_t size, const size_t pos )
{
#ifdef _DEBUG
  AXE_CHECK_DBG_ERROR( (NULL != data && 0 < size), AXE_ERROR_MSG_BAD_ARGUMENTS );
  bool  ok = state.file_list.search( (axe_list_item < axfs_file * > *) file_id );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif

  axfs_file*  file = ( (axe_list_item < axfs_file * > *) file_id )->data;

  file->insert_data( data, size, pos );

  return( AXE_TRUE );
}

/**
* Add data to the end of the file. Effects are inmediate
*/
AXFS_API int axfs_add_data( const AXE_ID file_id, const void* data, const size_t size )
{
#ifdef _DEBUG
  AXE_CHECK_DBG_ERROR( (NULL != data && 0 < size), AXE_ERROR_MSG_BAD_ARGUMENTS );
  bool  ok = state.file_list.search( (axe_list_item < axfs_file * > *) file_id );
  AXE_CHECK_DBG_ERROR( ok, AXE_ERROR_MSG_UNKNOWN_ID );
#endif

  axfs_file*  file = ( (axe_list_item < axfs_file * > *) file_id )->data;

  file->insert_data( data, size, file->get_size() );

  return( AXE_TRUE );
}

/* $Id: axfs_read_write.cpp,v 1.1 2004/05/02 16:32:31 doneval Exp $ */
