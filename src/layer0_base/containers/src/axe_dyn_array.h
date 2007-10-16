/**
* @file
* Dynamic array
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  04 Apr 2004
*/
#ifndef __AXE_DYN_ARRAY_H__
  #define __AXE_DYN_ARRAY_H__

  #include <new>
  #include <algorithm>
  #define AXE_DYN_ARRAY_DEFAULT_BLOCK_SIZE  25

/**
* Dinamically allocated array 
*/
template<class type>
class axe_dyn_array
{
  public:
    const type*   data;
    const long&   last_item;
    const long&   mem_size;
    const long&   block_size;
  private:
    long    _last_item;
    long    _mem_size;
    long    _block_size;
    type*   _data;
  public:

    /**
    * Constructor
    */
    axe_dyn_array( const long custom_block_size = AXE_DYN_ARRAY_DEFAULT_BLOCK_SIZE ) :
    _block_size( custom_block_size ),
    _last_item( 0 ),
    _mem_size( 0 ),
    mem_size( _mem_size ),
    block_size( _block_size ),
    last_item( _last_item ),
    data( _data )
    {
      _data = NULL;
      resize_data();
      _last_item = 0;
    }

    /**
    * Destructor
    */
    ~axe_dyn_array()
    {
      if( _data != NULL )
      {
        for( register long i = 0; i < _last_item; ++i )
        {
          _data[i].~type();
        }

        free( _data );
        _data = NULL;
        data = _data;
      }

      _mem_size = _block_size = 0;
      _last_item = 0;
    }

    /**
    * read / write access
    */
    type & operator [] (const long index)
    {
      AXE_ASSERT( index >= 0 && index < _last_item );
      return( _data[index] );
    }

    const type & operator [] (const long index) const
    {
      AXE_ASSERT( index >= 0 && index < _last_item );
      return( data[index] );
    }

    /**
    * Simply check if item exist
    */
    inline bool exist( const long index )
    {
      return( index >= 0 && index < _last_item );
    }

    /**
    * get first item
    */
    type& first()
    {
      AXE_ASSERT( _last_item > 0 );
      return( _data[0] );
    }

    /**
    * get last item
    */
    type& last()
    {
      AXE_ASSERT( _last_item > 0 );
      return( _data[_last_item - 1] );
    }

    /**
    * Asignation operator
    */
    axe_dyn_array &operator=( const axe_dyn_array<type>& array )
    {
      clear();
      operator +=( array );
      return( *this );
    }

    /**
    * Add other array
    */
    axe_dyn_array &operator+=( const axe_dyn_array<type>& array_to_add )
    {
      long  prev_last_item = _last_item;
      resize( array_to_add.last_item );

      std::copy( &array_to_add.data[0], &array_to_add.data[array_to_add.last_item], &_data[prev_last_item] );

      return( *this );
    }

    /**
    * Push a new element. Resize if needed
    */
    void push( const type& item, const long num_items = 1 )
    {
      AXE_ASSERT( num_items > 0 );

      long  prev_last_item = _last_item;
      resize( _last_item + num_items );

      for( register long i = 0; i < num_items; ++i )
      {
        _data[prev_last_item + i] = item;
      }
    }

    /**
    * Pushes an array of elements. Resize if needed
    */
    void push( const type* items, const long num_items )
    {
      AXE_ASSERT( items != NULL && num_items > 0 );

      long  prev_last_item = _last_item;
      resize( _last_item + num_items );

      for( register long i = 0; i < num_items; ++i )
      {
        _data[prev_last_item + i] = items[i];
      }
    }

    /**
    * Erases last element
    */
    type& pop()
    {
      AXE_ASSERT( _last_item > 0 );

      --_last_item;
      return( _data[last_item ] );
    }

    /**
    * Clears the list
    */
    void clear()
    {
      _last_item = 0;
    }

    /**
    * Removes and compact list
    */
    void remove( long start = 0, long end = -1 )
    {
      AXE_ASSERT( start >= 0 && start < last_item );
      AXE_ASSERT( end <= last_item );

      // case 1: last items
      if( end < 0 )
      {
        _last_item = start;
        return;
      }

      AXE_ASSERT( start <= end );

      // case 2: entire list
      if( 0 == start && _last_item == end )
      {
        clear();
        return;
      }

      // case 3: other pos
      register long i = start;
      register long k = end;

      for( ; k < _last_item; ++i, ++k )
      {
        _data[i] = _data[k];
      }

      _last_item -= ( end - start );
    }

    /**
    * Resize to a certain number of items
    * It won't free mem if new_max_size < current size
    */
    void resize( const long new_max_size )
    {
      if( new_max_size > _mem_size )
      {
        resize_data( new_max_size - _mem_size );
      }

      long  needed = new_max_size - _last_item;

      for( register long i = 0; i < needed; ++i )
      {
        type*   mem = new( &_data[_last_item + i] ) type;
        AXE_ASSERT( mem == &_data[_last_item + i] );
      }

      _last_item = new_max_size;
    }

    /**
    * foreach implementation using a C callback
    */
    int foreach( int (*foreach_callback) (type &item, const long index) )
    {
      for( register long i = 0; i < _last_item; ++i )
      {
        if( AXE_FALSE == (*foreach_callback) (_data[i], i) )
        {
          return( AXE_FALSE );
        }
      }

      return( AXE_TRUE );
    }

    /**
    * swap two values
    */
    void swap( long index1, long index2 )
    {
      AXE_ASSERT( index1 >= 0 && index1 < _last_item );
      AXE_ASSERT( index2 >= 0 && index2 < _last_item );

      if( index1 == index2 )
      {
        return;
      }

      type  tmp = _data[index1];
      _data[index1] = data[index2];
      _data[index2] = tmp;
    }

    /**
    * quicksort implementation
    * sort_callback must return AXE_FALSE if item1 < item2 (or change to alter the sort order)
    */
    void sort( int (*sort_callback) (type &item1, type &item2), long first = 0, long last = -1 )
    {
      long  last_pos = ( last < 0 ) ? _last_item - 1 : last;
      long  left = first - 1;
      long  right = last_pos;

      type  item = _data[last_pos];

      if( first >= last_pos )
      {
        return;
      }

      while( true )
      {
        while( (*sort_callback) (_data[++left], item) )
        {
          if( left >= last_pos )
          {
            break;
          }
        }

        while( (*sort_callback) (item, _data[--right]) )
        {
          if( right == 0 )
          {
            break;
          }
        }

        if( left >= right )
        {
          break;
        }

        swap( left, right );
      }

      swap( left, last_pos );
      sort( sort_callback, first, left - 1 );
      sort( sort_callback, left + 1, last );
    }

  private:

    /**
    * Resize the array
    */
    void resize_data( const long min = 1 )
    {
      _mem_size += max( min, block_size );
      _data = (type*) realloc( _data, (sizeof(type) * _mem_size) );
      data = _data;
    }
};
#endif // __AXE_DYN_ARRAY_H__

/* $Id: axe_dyn_array.h,v 1.9 2004/09/05 21:35:11 ilgenio Exp $ */
