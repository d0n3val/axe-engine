/**
* @file
* 
* @author    Carlos Fuentes
* @date      22 Aug 2004
*/
#ifndef __AXE_SEQUENTIAL_BUFFER_H__
  #define __AXE_SEQUENTIAL_BUFFER_H__

/*$1-  main definitions for Axe libs -----------------------------------------*/
  #include "axe_defs.h"

/*$1- Lib version ------------------------------------------------------------*/
  #define AXE_SEQUENTIAL_BUFFER_VERSION 1
  #define AXE_SEQUENTIAL_BUFFER_NAME    "SEQUENTIAL_BUFFER"
  #define AXE_SEQUENTIAL_BUFFER_LIBID   'AXSB'

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXSB_API  __declspec( dllexport )
    #pragma message( "Compiling Axe 'sequential buffer' library ..." )
  #else
    #define AXSB_API  __declspec( dllimport )
    #pragma message( "Using Axe 'sequential buffer' library ..." )

/*$1-  Automatic .lib link ---------------------------------------------------*/
    #ifndef AXSB_NO_AUTOLINK
      #pragma comment( lib, "axe_sequential_buffer.lib" )
    #endif
  #endif

/*$1-States for this lib -----------------------------------------------------*/
enum axsb_states
{
  AXSB_VERSION      = 1,
  AXSB_LIBRARY_NAME,
  AXSB_LIBRARY_ID,
  AXSB_DEBUG_MODE,
  AXSB_LAST_ERROR,
  AXSB_STATE_COUNT
};

/*$1-Seek position -----------------------------------------------------------*/
enum axsb_seek_pos
{
  AXSB_SEEK_BEGIN   = 0,
  AXSB_SEEK_CURRENT,
  AXSB_SEEK_END
};

typedef long  axsb_buffer_id;

extern "C"
{

  /*$1- axsb_sequential_buffer.cpp -------------------------------------------*/
  AXSB_API unsigned int axsb_get( const int query_state );
  AXSB_API unsigned int axsb_set( const int query_state, const unsigned int new_value );
  AXSB_API const char*  axsb_get_error_message( const unsigned int error_number );
  AXSB_API int          axsb_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axsb_buffer.cpp ------------------------------------------------------*/
  AXSB_API axsb_buffer_id axsb_create_buffer( const void* ptr, size_t size );
  AXSB_API void           axsb_release_all( void );
  AXSB_API void           axsb_release_buffer( axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_set_buffer( axsb_buffer_id buffer );
  AXSB_API bool           axsb_seek( axsb_seek_pos seek_pos, size_t offset, axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_read( void* ptr, size_t size, axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_read_string( void* ptr, size_t max_size, axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_write( const void* ptr, size_t size, axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_eob( axsb_buffer_id buffer = -1 );
  AXSB_API size_t         axsb_tell( axsb_buffer_id buffer = -1 );

  /*$1- axsb_chunck.cpp ------------------------------------------------------*/
  AXSB_API unsigned short axsb_get_read_chunck_id( axsb_buffer_id buffer = -1 );
  AXSB_API size_t         axsb_get_read_chunck_start( axsb_buffer_id buffer = -1 );
  AXSB_API size_t         axsb_get_read_chunck_size( axsb_buffer_id buffer = -1 );
  AXSB_API unsigned short axsb_begin_read_chunk( axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_end_read_chunck( axsb_buffer_id buffer = -1 );

  AXSB_API unsigned short axsb_get_write_chunck_id( axsb_buffer_id buffer = -1 );
  AXSB_API size_t         axsb_get_write_chunck_start( axsb_buffer_id buffer = -1 );
  AXSB_API size_t         axsb_get_write_chunck_size( axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_begin_write_chunk( unsigned short chunck_id, axsb_buffer_id buffer = -1 );
  AXSB_API bool           axsb_end_write_chunck( axsb_buffer_id buffer = -1 );
} // extern "C"
#endif // __AXE_SEQUENTIAL_BUFFER_H__

/* $Id: axe_sequential_buffer.h,v 1.6 2004/08/29 13:01:22 ilgenio Exp $ */
