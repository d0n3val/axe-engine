/**
* @file
* Any class based on http://www.two-sdg.demon.co.uk/curbralan/papers/ValuedConversions.pdf
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  07 Dec 2007
*/
#ifndef __AXE_ANY_H__
  #define __AXE_ANY_H__

#include <typeinfo.h>
#include "axe_list.h"

#define AXE_ANY_IS_TYPE(any, type) ( any.type_info() == typeid(type) )
#define AXE_ANY_IS_SAME_TYPE(any, type) ( any.type_info() == typeid(type) )

/**
* Generic type store class
*/
class axe_any
{
  public:

    /*$1- COnstructors & Destructor ------------------------------------------*/
    axe_any() : content( 0 )
    {}

    axe_any(const axe_any &other) : content( other.content ? other.content->clone() : 0 )
    {}

    template<typename VALUE_TYPE>
    axe_any(const VALUE_TYPE &value) : content( new holder<VALUE_TYPE>( value ) )
    {}

    ~axe_any()
    {
     AXE_RELEASE( content );
    }
    
    /*$1- Assignment ---------------------------------------------------------*/
    axe_any& swap(axe_any &other)
    {
      axe_swap( content, other.content );
      return( *this );
    }

    axe_any& operator=(const axe_any &other)
    {
      axe_any( other ).swap( *this );
      return( *this );
    }

    template<typename VALUE_TYPE>
    axe_any& operator=(const VALUE_TYPE &other)
    {
      axe_any( other ).swap( *this );
      return( *this );
    }

    /*$1- Cast ---------------------------------------------------------------*/
    operator const void *() const
    {
      return( content );
    }

    template<typename VALUE_TYPE>
    const VALUE_TYPE *to_ptr() const
    {
      return( type_info() == typeid(VALUE_TYPE) ? &static_cast< holder<VALUE_TYPE> *>(content)->held : 0 );
    }

    template<typename VALUE_TYPE>
    friend VALUE_TYPE * any_cast(axe_any *);

    /*$1- Utility ------------------------------------------------------------*/
    template<typename VALUE_TYPE>
    bool copy_to(VALUE_TYPE &value) const
    {
      const VALUE_TYPE *copyable = to_ptr<VALUE_TYPE>();

      if( copyable )
      {
        value = *copyable;
      }

      return( copyable );
    }

    const std::type_info & type_info() const
    {
      return( content ? content->type_info() : typeid ( void ) );
    }

    bool empty() const
    {
      return( content == 0 );
    }

  private:

    /*$1- Variable definition ------------------------------------------------*/
    struct placeholder
    {
      virtual ~placeholder() 
      {}

      virtual const std::type_info & type_info() const = 0;
      virtual placeholder*           clone()     const = 0;
    };

    template<typename VALUE_TYPE>
    struct holder : public placeholder
    {
      holder (const VALUE_TYPE &value) : held( value )
      {}

      virtual const std::type_info & type_info() const
      {
        return( typeid( VALUE_TYPE ) );
      }

      virtual placeholder* clone() const
      {
        return( new holder( held ) );
      }

      VALUE_TYPE held;
    };

    placeholder* content;
};

/*$1- More conversions -------------------------------------------------------*/
template<typename VALUE_TYPE>
VALUE_TYPE * any_cast(axe_any * operand)
{
  return( (operand && operand->type_info() == typeid(VALUE_TYPE)) ? &static_cast<axe_any::holder<VALUE_TYPE> *>(operand->content)->held : 0 );
}

template<typename VALUE_TYPE>
const VALUE_TYPE * any_cast(const axe_any * operand)
{
    return( any_cast<VALUE_TYPE>( const_cast<axe_any *>(operand) ) );
}

template<typename VALUE_TYPE>
VALUE_TYPE any_cast(const axe_any & operand)
{
  const VALUE_TYPE * result = operand.to_ptr<VALUE_TYPE>();
  return( result ? *result : throw std::bad_cast() );
}

template<typename VALUE_TYPE>
VALUE_TYPE any_cast(axe_any & operand)
{
  VALUE_TYPE * result = any_cast<VALUE_TYPE>(&operand);
  return( result ? *result : throw std::bad_cast() );
}

/*$1- Useful typedefs --------------------------------------------------------*/
typedef axe_list<axe_any> axe_many;

#endif // __AXE_ANY_H__

/* $Id: axe_bitset.h,v 1.2 2004/07/21 22:08:50 doneval Exp $ */
