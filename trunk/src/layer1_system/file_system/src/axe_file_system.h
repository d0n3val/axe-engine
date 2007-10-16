/**
* @file
* Manages files and directories
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @version   1.0
* @date      28 Mar 2004
*/
#ifndef __AXE_FILE_SYSTEM_H__
  #define __AXE_FILE_SYSTEM_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXFS_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'File System' ..." )
  #else
    #define AXFS_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'File System' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXFS_NO_AUTOLINK
      #pragma comment( lib, "axe_file_system.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axfs_states
{
  AXFS_VERSION      = 1,
  AXFS_LIBRARY_NAME,
  AXFS_LIBRARY_ID,
  AXFS_DEBUG_MODE,
  AXFS_LAST_ERROR,
  AXFS_STATE_COUNT
};

/** @example axfs_test.cpp */
extern "C"
{

  /*$1- axfs_file_system.cpp -------------------------------------------------*/
  AXFS_API unsigned int axfs_get( const int query_state );
  AXFS_API unsigned int axfs_set( const int query_state, const unsigned int new_value );
  AXFS_API const char*  axfs_get_error_message( const unsigned int error_number );
  AXFS_API int          axfs_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axfs_create.cpp ------------------------------------------------------*/
  AXFS_API const AXE_ID axfs_create( const char* file_name, const int reload=AXE_FALSE );
  AXFS_API int          axfs_destroy( const AXE_ID file_id, const int delete_file );

  /*$1- axfs_read_write.cpp --------------------------------------------------*/
  AXFS_API const void*  axfs_get_data( const AXE_ID file_id, const int reload=AXE_FALSE );
  AXFS_API int          axfs_set_data( const AXE_ID file_id, const void* data, const size_t size );
  AXFS_API int          axfs_add_data( const AXE_ID file_id, const void* data, const size_t size );
  AXFS_API int          axfs_insert_data( const AXE_ID file_id, const void* data, const size_t size, const size_t pos );

  /*$1- axfs_get_info.cpp ----------------------------------------------------*/
  AXFS_API const char*  axfs_get_name( const AXE_ID file_id );
  AXFS_API unsigned int axfs_get_size( const AXE_ID file_id );

  /*$1- axfs_util.cpp --------------------------------------------------------*/
  AXFS_API int    axfs_file_exists( const char* file_name );
  AXFS_API size_t axfs_file_size( const char* file_name );
  AXFS_API int    axfs_delete_file( const char* file_name );
  AXFS_API int    axfs_rename_file( const char* file_name, const char* new_file_name );

  /*$1- axfs_directory.cpp ---------------------------------------------------*/
  AXFS_API const char*  axfs_get_current_dir();
  AXFS_API int          axfs_change_dir( const char* new_dir );
  AXFS_API int          axfs_create_dir( const char* new_dir );
  AXFS_API int          axfs_remove_dir( const char* dir );

  // gestion de swapping, con una "ventana" en memoria y tal
  // cuantos archivos hay en el directorio,
  // lista de archivos de un directorio
  // esto es un archivo o un directorio?
  // limpiar toda la memoria (borrar todos los file)
  // cuanta memoria estamos usando?
  // lista de archivos que cumplan wildcards (regex) de un directorio
} // extern "C"
#endif // __AXE_FILE_SYSTEM_H__

/* $Id: axe_file_system.h,v 1.2 2004/07/21 22:08:51 doneval Exp $ */
