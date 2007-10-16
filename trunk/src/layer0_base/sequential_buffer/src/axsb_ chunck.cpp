/**
* @file
* read_chuncks read/write buffer file
*/
#include "axsb_stdafx.h"

extern axe_dyn_array<axsb_buffer_info>  buffers; 
extern axsb_state                       state;

/**
* gets chunck id
*/
AXSB_API unsigned short axsb_get_read_chunck_id( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  AXE_CHECK_DBG_ERROR( buffer_info.read_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );
  return( buffer_info.read_chuncks.last().id );
}

/**
* gets chunck id
*/
AXSB_API unsigned short axsb_get_write_chunck_id( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  AXE_CHECK_DBG_ERROR( buffer_info.write_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );
  return( buffer_info.write_chuncks.last().id );
}

/**
* gets chunck start offset
*/
AXSB_API size_t axsb_get_read_chunck_start( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  AXE_CHECK_DBG_ERROR( buffer_info.read_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );
  return( buffer_info.read_chuncks.last().start );
}

/**
* gets chunck start offset
*/
AXSB_API size_t axsb_get_write_chunck_start( axsb_buffer_id buffer )
{
    AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
    if( buffer < 0 )
    {
        buffer = state.default_buffer;
    }

    AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

    axsb_buffer_info&  buffer_info = buffers[buffer];
    AXE_CHECK_DBG_ERROR( buffer_info.write_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );
    return( buffer_info.write_chuncks.last().start );
}

/**
* gets chunck size
*/
AXSB_API size_t axsb_get_read_chunck_size( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  AXE_CHECK_DBG_ERROR( buffer_info.read_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );
  return( buffer_info.read_chuncks.last().size );
}

/**
* gets chunck size
*/
AXSB_API size_t axsb_get_write_chunck_size( axsb_buffer_id buffer )
{
    AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
    if( buffer < 0 )
    {
        buffer = state.default_buffer;
    }

    AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

    axsb_buffer_info&  buffer_info = buffers[buffer];
    AXE_CHECK_DBG_ERROR( buffer_info.write_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );
    return( buffer_info.write_chuncks.last().size );
}

/**
* begins read chunck
*/
AXSB_API unsigned short axsb_begin_read_chunk( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  axsb_chunck_info  chunck;
  chunck.start = buffer_info.offset;
  axsb_read( &chunck.id, sizeof(chunck.id), buffer );
  axsb_read( &chunck.size, sizeof(chunck.size), buffer );
  buffer_info.read_chuncks.push( chunck );

  return( buffer_info.read_chuncks.last().id );
}

/**
* ends read chunck
*/
AXSB_API bool axsb_end_read_chunck( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];

  AXE_CHECK_DBG_ERROR( buffer_info.read_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );

  axsb_chunck_info&   chunck = buffer_info.read_chuncks.last();
  axsb_seek( AXSB_SEEK_BEGIN, chunck.start + chunck.size, buffer);
  buffer_info.read_chuncks.pop();

  return( AXE_TRUE ); 
}

/**
* begins write chunck
*/
AXSB_API bool axsb_begin_write_chunk( unsigned short chunck_id, axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  axsb_chunck_info  chunck;
  chunck.start = axsb_tell( buffer );
  chunck.id = chunck_id;
  chunck.size = 0;

  axsb_write( &chunck.id, sizeof(chunck.id), buffer );
  axsb_write( &chunck.size, sizeof(chunck.size), buffer );

  buffer_info.write_chuncks.push( chunck );

  return( AXE_TRUE );
}

/**
* ends write chunck
*/
AXSB_API bool axsb_end_write_chunck( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];

  AXE_CHECK_DBG_ERROR( buffer_info.write_chuncks.last_item > 0, AXE_ERROR_MSG_NO_CHUNCKS );

  axsb_chunck_info&   chunck = buffer_info.write_chuncks.last();
  chunck.size = axsb_tell( buffer ) - chunck.start;
  axsb_seek( AXSB_SEEK_BEGIN, chunck.start, buffer );
  axsb_write( &chunck.id, sizeof(chunck.id), buffer );
  axsb_write( &chunck.size, sizeof(chunck.size), buffer );
  axsb_seek( AXSB_SEEK_BEGIN, chunck.start + chunck.size, buffer );

  buffer_info.write_chuncks.pop();

  return( AXE_TRUE );
}
