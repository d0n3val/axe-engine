#include "axsb_stdafx.h"

axe_dyn_array<axsb_buffer_info> buffers;
extern axsb_state               state;

/**
* creates a sequential buffer
*/
AXSB_API axsb_buffer_id axsb_create_buffer( const void* ptr, size_t size )
{
  AXE_ASSERT( NULL != ptr && size > 0 );

  axsb_buffer_info  buffer;
  buffer.ptr = (char*) ptr;
  buffer.size = size;
  buffer.offset = 0;
  buffers.push( buffer );

  return( buffers.last_item-1 );
}

/**
* releases all buffers
*/
AXSB_API void axsb_release_all( void )
{
  buffers.clear();
}

/**
* releases a buffer
*/
AXSB_API void axsb_release_buffer( axsb_buffer_id buffer )
{
  AXE_ASSERT( buffer < buffers.last_item );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_ASSERT( buffer >= 0 );

  buffers.remove( buffer, buffer + 1 );
}

/**
* Sets the buffer
*/
AXSB_API bool axsb_set_buffer( axsb_buffer_id buffer )
{
  AXE_ASSERT( buffer < buffers.last_item );
  state.default_buffer = buffer;

  return( AXE_TRUE );
}

/**
* Seeks the buffer
*/
AXSB_API bool axsb_seek( axsb_seek_pos seek_pos, size_t offset, axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );
  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];

  switch( seek_pos )
  {
    case AXSB_SEEK_BEGIN:
      buffer_info.offset = offset;
      break;

    case AXSB_SEEK_END:
      buffer_info.offset = buffer_info.size + offset;
      break;

    case AXSB_SEEK_CURRENT:
      buffer_info.offset += offset;
  }

  return( AXE_TRUE );
}

/**
* reads data from buffer (copies data to ptr)
*/
AXSB_API bool axsb_read( void* ptr, size_t size, axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );

  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];

  if( AXE_TRUE == axsb_eob(buffer) )
  {
    return( AXE_TRUE );
  }

  size_t  real_size = min( buffer_info.size - buffer_info.offset, size );
  memcpy( ptr, (buffer_info.ptr + buffer_info.offset), real_size );
  buffer_info.offset += real_size;

  return( AXE_TRUE );
}

/**
* reads a 0 terminated string from buffer
*/
AXSB_API bool axsb_read_string( void* ptr, size_t max_size, axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );

  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];

  if( AXE_TRUE == axsb_eob(buffer) )
  {
    return( AXE_TRUE );
  }

  size_t  real_size = min( buffer_info.size - buffer_info.offset, max_size - 1 );
  size_t  str_length = strlen( buffer_info.ptr + buffer_info.offset );
  real_size = min( real_size, str_length + 1 );
  memcpy( ptr, (buffer_info.ptr + buffer_info.offset), real_size );
  ((char*)ptr)[real_size + 1] = 0; // Null terminated string
  buffer_info.offset += ( str_length + 1 );

  return( AXE_TRUE );
}

/**
* writes data to buffer
*/
AXSB_API bool axsb_write( const void* ptr, size_t size, axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );

  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];

  if( AXE_TRUE == axsb_eob(buffer) )
  {
    return( AXE_TRUE );
  }

  size_t  real_size = min( buffer_info.size - buffer_info.offset, size );
  memcpy( buffer_info.ptr + buffer_info.offset, ptr, real_size );
  buffer_info.offset += real_size;

  return( AXE_TRUE );
}

/**
* end of buffer ?
*/
AXSB_API bool axsb_eob( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );

  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  return( buffer_info.offset >= buffer_info.size );
}

/**
* returns buffer offsetº
*/
AXSB_API size_t axsb_tell( axsb_buffer_id buffer )
{
  AXE_CHECK_DBG_ERROR( buffer < buffers.last_item, AXE_ERROR_MSG_BUFFER_INCORRECT );

  if( buffer < 0 )
  {
    buffer = state.default_buffer;
  }

  AXE_CHECK_DBG_ERROR( buffer >= 0, AXE_ERROR_MSG_BUFFER_INCORRECT );

  axsb_buffer_info&  buffer_info = buffers[buffer];
  return( min(buffer_info.offset, buffer_info.size) );
}
