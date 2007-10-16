/**
* @file
* Static array
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  04 Apr 2004
*/
#ifndef __AXE_STC_ARRAY_H__
  #define __AXE_STC_ARRAY_H__

/**
* Static size array
*/
template<class type, long custom_size>
class axe_stc_array
{
  public:
    const long&   size;
    const type*   data;
  private:
    long  _size;
    type  _data[custom_size];
  public:

    /**
    * Constructor
    */
    axe_stc_array() :
    size( _size ),
    data( &_data[0] ) {
      AXE_ASSERT( custom_size > 0 );
      _size = custom_size;
    }

    /**
    * Destructor
    */
    ~axe_stc_array() {
    }

    /**
    * read / write access
    */
    type & operator [] (long index) {
      AXE_ASSERT( index >= 0 && index < _size );
      return( _data[index] );
    }

    /**
    * get first item
    */
    type& first() {
      AXE_ASSERT( _size > 0 );
      return( _data[0] );
    }

    /**
    * get last item
    */
    type& last() {
      AXE_ASSERT( _size > 0 );
      return( _data[_size - 1] );
    }

    /**
    * Asignation operator
    */
    axe_stc_array &operator=( const axe_stc_array<type, custom_size> array ) {
      AXE_ASSERT( array.size == custom_size );

      for( register long i = 0; i < custom_size; ++i ) {
        _data[i] = array.data[i];
      }
      //memcpy( _data, array.data, custom_size * sizeof(type) );

      return( *this );
    }

    /**
    * foreach implementation using a C callback
    */
    int foreach( int (*foreach_callback) (type &item, const long index) ) {
      for( register long i = 0; i < _size; ++i ) {
        if( AXE_FALSE == (*foreach_callback) (_data[i], i) ) {
          return( AXE_FALSE );
        }
      }

      return( AXE_TRUE );
    }

    /**
    * swap two values
    */
    void swap( long index1, long index2 ) {
      AXE_ASSERT( index1 >= 0 && index1 < _size );
      AXE_ASSERT( index2 >= 0 && index2 < _size );

      if( index1 == index2 ) {
        return;
      }

      type  tmp = _data[index1];
      _data[index1] = _data[index2];
      _data[index2] = tmp;
    }

    /**
    * quicksort implementation
    */
    void sort( int (*sort_callback) (type &item1, type &item2), long first = 0, long last = -1 ) {
      long  last_pos = ( last < 0 ) ? _size - 1 : last;
      long  left = first - 1;
      long  right = last_pos;

      type  item = _data[last_pos];

      if( first >= last_pos ) {
        return;
      }

      while( true ) {
        while( (*sort_callback) (_data[++left], item) ) {
          if( left >= last_pos ) {
            break;
          }
        }

        while( (*sort_callback) (item, _data[--right]) ) {
          if( right == 0 ) {
            break;
          }
        }

        if( left >= right ) {
          break;
        }

        swap( left, right );
      }

      swap( left, last_pos );
      sort( sort_callback, first, left - 1 );
      sort( sort_callback, left + 1, last );
    }
};
#endif // __AXE_STC_ARRAY_H__

/* $Id: axe_stc_array.h,v 1.4 2004/07/21 22:08:50 doneval Exp $ */
