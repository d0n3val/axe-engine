/**
* @file
* Serialize functions
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      28 Mar 2004
*/
#include "axst_stdafx.h"

/**
* Load data from memory, format is SIZE+DATA (uint+chars)
*/
size_t axe_string::load( const char* mem, size_t max_size )
{
  AXE_ASSERT( mem != NULL );

  /* Cogemos el tamaño a leer */
  unsigned int  s;
  memcpy( &s, mem, sizeof(unsigned int) );

  /* Comprobamos que tenemos memoria suficiente */
  size_t  readed = ( sizeof(char) * s ) + sizeof( unsigned int );
  AXE_ASSERT( readed < max_size );

  /* Copiamos memoria */
  size = s;
  reserve( size );
  memcpy( string, (const void*) (mem + sizeof(unsigned int)), sizeof(char) * size );
  string[size] = 0;
  calc_checksum();

  return( readed );
}

/**
* Save data to memory, format is SIZE+DATA (uint+chars)
*/
size_t axe_string::save( char* mem, size_t max_size ) const
{
  AXE_ASSERT( mem != NULL );

  /* Comprobamos que tenemos memoria suficiente */
  size_t  written = ( sizeof(char) * size ) + sizeof( unsigned int );
  AXE_ASSERT( written < max_size );

  /* Copiamos memoria */
  memcpy( mem, &size, sizeof(unsigned int) );
  memcpy( (void*) (mem + sizeof(unsigned int)), string, sizeof(char) * size );

  return( written );
}
