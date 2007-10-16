/**
* @file
* Bit field implementation
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  13 Jun 2004
*/
#ifndef __AXE_BITSET_H__
  #define __AXE_BITSET_H__

  #include "math.h"

/**
* Static size array
*/
template<long custom_size>
class axe_bitset
{
  public:
    const long&   size;
    const bool*   data;
  private:
    long  _size;
    bool  _data[custom_size];
  public:

    /**
    * Constructor
    */
    axe_bitset() :
    size( _size ),
    data( _data )
    {
      AXE_ASSERT( custom_size > 0 );
      _size = custom_size;
    }

    /**
    * Destructor
    */
    ~axe_bitset()
    {
    }

    /**
    * create from int
    */
    void create( const int flags, const int size )
    {
      AXE_ASSERT( _size >= (long) size );
      AXE_ASSERT( size < sizeof(flags) * 8 );

      for( register int i = 0, pow2 = 1; i < size; ++i, pow2 *= 2 )
      {
        _data[i] = ( (flags & pow2) == pow2 );
      }
    }

    /**
    * Check if flags enabled in this integer exist
    */
    bool check_enabled( const int flags, const int size )
    {
      AXE_ASSERT( _size >= (long) size );

      if( 0 == flags )
      {
        return( _data[0] );
      }

      for( register int i = 0, pow2 = 1; i < size; ++i, pow2 *= 2 )
      {
        if( (flags & pow2) == pow2 )
        {
          if( _data[i] != true )
          {
            return( false );
          }
        }
      }

      return( true );
    }

    /**
    * reset all bits to a value
    */
    void zero( const bool value = false )
    {
      memset( _data, (int) value, _size );
    }

    /**
    * read / write access
    */
    bool & operator [] (const long index)
    {
      AXE_ASSERT( index >= 0 && index < _size );
      return( _data[index] );
    }

    /**
    * asig operator
    */
    axe_bitset &operator=( const axe_bitset<custom_size>& bitset )
    {
      memcpy( _data, bitset.data, custom_size );

      return( *this );
    }
};
#endif // __AXE_BITSET_H__

/* $Id: axe_bitset.h,v 1.2 2004/07/21 22:08:50 doneval Exp $ */
