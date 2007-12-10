/**
* @file
* Double linked list
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  04 Apr 2004
*/
#ifndef __AXE_LIST_H__
  #define __AXE_LIST_H__

/*$ off */

/*$1- Macro to delete all elements of the list -------------------------------*/
  #define AXE_LIST_DELETE_ELEMENTS( list, data_type ) \
  {                                                   \
    axe_list_item<data_type>*   item = list.start;    \
    while( item != NULL )                             \
    {                                                 \
      AXE_RELEASE( item->data );                      \
      item = item->next;                              \
    }                                                 \
  }

/*$1- Macro to delete all elements of the list (array version) ---------------*/
  #define AXE_LIST_DELETE_ARRAY_ELEMENTS( list, data_type ) \
  {                                                         \
    axe_list_item<data_type>*   item = list.start;          \
    while( item != NULL )                                   \
    {                                                       \
      AXE_RELEASE_ARRAY( item->data );                      \
      item = item->next;                                    \
    }                                                       \
  }

/*$1- Macro to loop entire list ----------------------------------------------*/
  #define AXE_LIST_FOR( list, data_type )             \
  for(                                                \
    axe_list_item < data_type > *p_item = list.start; \
    p_item != NULL;                                   \
    p_item = p_item->next )

/*$1- Macro to loop entire list ----------------------------------------------*/
  #define AXE_LIST_FOR_ITEM( list, data_type, p_item ) \
  for(                                                 \
    axe_list_item < data_type > *p_item = list.start;  \
    p_item != NULL;                                    \
    p_item = p_item->next )

/**
* Contains items from double linked list
*/
template<class tdata>
struct axe_list_item
{
  tdata                   data;
  axe_list_item<tdata>*   next;
  axe_list_item<tdata>*   prev;

  inline axe_list_item( const tdata& _data )
  {
    data = _data;
    next = prev = NULL;
  }

  ~axe_list_item()
  {
  }
};

/**
* Manages a double linked list
*/
template<class tdata>
class axe_list
{
  public:
    const long&             size;
    axe_list_item<tdata>*   start;
    axe_list_item<tdata>*   end;
  protected:
    long  _size;
  public:

    /**
    * Constructor
    */
    inline axe_list() :
    size( _size )
    {
      start = end = NULL;
      _size = 0;
    }

    /**
    * Copy Constructor
    */
    axe_list(const axe_list<tdata>& list) : size( _size )
    {
      start = end = NULL;
      _size = 0;

      // add all elements in the other list
      axe_list_item<tdata>*   item;

      item = list.start;
      while( item != NULL )
      {
        add( item->data );
        item = item->next;
      }
    }

    /**
    * Destructor
    */
    ~axe_list()
    {
      clear();
    }

    /**
    * Asig operator
    */
    axe_list &operator=( const axe_list<tdata>& list )
    {
      // erase me
      clear();

      // add all elements in the other list
      axe_list_item<tdata>*   item;

      item = list.start;
      while( item != NULL )
      {
        add( item->data );
        item = item->next;
      }

      return( *this );
    }

    /**
    * read / write operator access directly to a position in the list
    */
    tdata & operator  [] (const long index)
    {
      AXE_ASSERT( index >= 0 && index < _size );

      long                    pos;
      axe_list_item<tdata>*   p_item;

      pos = 0;
      p_item = start;

      while( p_item != NULL )
      {
        if( pos == index )
        {
          break;
        }

        ++pos;
        p_item = p_item->next;
      }

      return( p_item->data );
    }

    /**
    * Add new item
    */
    inline void add( const tdata& item )
    {
      axe_list_item<tdata>*   p_data_item;

      p_data_item = new axe_list_item < tdata > ( item );

      if( start == NULL )
      {
        start = end = p_data_item;
      }
      else
      {
        p_data_item->prev = end;
        end->next = p_data_item;
        end = p_data_item;
      }

      ++_size;
    }

    /**
	  * Deletes an item from the list
	  */
    inline bool del( axe_list_item<tdata>* item = NULL )
    {
      AXE_ASSERT( item != NULL );

      // Now reconstruct the list
      if( item->prev != NULL )
      {
        item->prev->next = item->next;
        if( item->next != NULL )
        {
          item->next->prev = item->prev;
        }
        else
        {
          end = item->prev;
        }
      }
      else
      {
        if( item->next )
        {
          item->next->prev = NULL;
          start = item->next;
        }
        else
        {
          start = end = NULL;
        }
      }

      AXE_RELEASE( item );
      --_size;

      return( true );
    }

    /**
	  * Search for a <tdata> in the list
	  */
    inline axe_list_item<tdata>* search( const tdata& item_to_search ) const
    {
      axe_list_item<tdata>*   item;

      item = start;
      while( item != NULL )
      {
        if( item->data == item_to_search )
        {
          break;
        }

        item = item->next;
      }

      // If not found, NULL will be returned
      return( item );
    }

    /**
    * Search for a axe_item in the list
    */
    inline bool search( const axe_list_item<tdata>* item_to_search ) const
    {
      axe_list_item<tdata>*   item;

      item = start;
      while( item != item_to_search )
      {
        if( item == NULL )
        {
          return( false );
        }

        item = item->next;
      }

      return( true );
    }

    /**
    * Returns the first position of the list
    */
    inline bool first( tdata* item ) const
    {
      if( _size <= 0 )
      {
        return( false );
      }

      item = &start->data;
      return( true );
    }

    /**
    * Returns the last position of the list
    */
    inline bool last( tdata* item ) const
    {
      if( _size <= 0 )
      {
        return( false );
      }

      item = &end->data;
      return( true );
    }

    /**
    * foreach implementation using a C callback
    */
    int foreach( int (*foreach_callback) (tdata &item, const long index) )
    {
      // add all elements in the other list
      axe_list_item<tdata>*   item;

      item = start;

      long  i = -1;
      while( item != NULL )
      {
        if( AXE_FALSE == (*foreach_callback) (item->data, ++i) )
        {
          return( AXE_FALSE );
        }

        item = item->next;
      }

      return( AXE_TRUE );
    }

    /**
    * Destroy and free all mem
    */
    inline void clear()
    {
      axe_list_item<tdata>*   p_data;
      axe_list_item<tdata>*   p_next;

      p_data = start;
      while( p_data != NULL )
      {
        p_next = p_data->next;
        AXE_RELEASE( p_data );
        p_data = p_next;
      }
      start = end = NULL;
      _size = 0;
    }
};
#endif /*__AXE_LIST_H__*/
