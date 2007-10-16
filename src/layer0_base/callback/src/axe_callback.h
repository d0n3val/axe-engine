/**
* @file
* 'Callback' lib PUBLIC header
* @author    Carlos Fuentes de los Santos
* @date      1 Apr 2004
*/
#ifndef __AXE_CALLBACK_H__
  #define __AXE_CALLBACK_H__

// toDO - Crear container con tipo específico para argumentos void;
/**
* Base class for callbacks
*/
template<class return_type, class param_type>
class axcb_callbackcontainer
{
  public:
    virtual return_type operator () ( param_type ) const = 0;
};

/**
* Contains a function pointer
*/
template<class return_type, class param_type>
class axcb_callbackfunction : public axcb_callbackcontainer<return_type, param_type>
{
  private:
    typedef return_type ( *function ) ( param_type );         //< callback function pointer typedef
    function  m_function;                                     //< the function to call
  public:
    /// Constructor
    axcb_callbackfunction( function _function ) {
      AXE_ASSERT( _function != 0 );
      m_function = _function;
    }

    /// Destructor
    ~axcb_callbackfunction( void ) {
      m_function = 0;
    }

    /// Does the function pointer call
    return_type operator () ( param_type _param ) const
    {
      AXE_ASSERT( m_function != 0 );
      return( (*m_function) (_param) );
    }
};

/**
* Contains a method pointer
*/
template<class Object, class return_type, class param_type>
class axcb_callbackmethod : public axcb_callbackcontainer<return_type, param_type>
{
  private:
    typedef return_type ( Object:: *Method ) ( param_type );  //< callback method pointer typedef
    Object*   m_object;                                       //< the object that contains the method to call
    Method    m_method;                                       //< the method to call
  public:
    /// Constructor
    axcb_callbackmethod( Object * _object, Method _method ) {
      AXE_ASSERT( _object != 0 && _method != 0 );
      m_object = _object;
      m_method = _method;
    }

    /// Destructor
    ~axcb_callbackmethod( void ) {
      m_object = 0;
      m_method = 0;
    }

    /// Does method call
    template<class Object, class return_type>
    return_type operator () (void) const
    {
      AXE_ASSERT( m_object != 0 && m_method != 0 );
      return( (m_object->*m_method) () );
    }

    /// Does the method call
    return_type operator () ( param_type _param ) const
    {
      AXE_ASSERT( m_object != 0 && m_method != 0 );
      return( (m_object->*m_method) (_param) );
    }
};
#endif // __AXE_CALLBACK_H__

/* $Id: axe_callback.h,v 1.3 2004/08/31 08:10:43 doneval Exp $ */
