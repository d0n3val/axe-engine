/**
* @file
* Single file class management
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      01 Apr 2004
*/
#ifndef __AXFS_FILE_H__
  #define __AXFS_FILE_H__

  #include "axfs_stdafx.h"

/**
* File read/write class
*/
class axfs_file
{
  public:
    int         fp;
    axe_string  file_name;
    size_t      size;
    void*       data;
  public:
    axfs_file( const char* file_name );
    ~axfs_file();

    bool          is_ok();
    const void*   get_data( const bool use_cache = true );
    size_t        get_size( const bool use_cache = true );
    bool          set_data( const void* data, const size_t size );
    bool          insert_data( const void* data, const size_t size, const size_t pos );
};
#endif // __AXFS_FILE_H__

/* $Id: axfs_file.h,v 1.1 2004/05/02 16:32:31 doneval Exp $ */
