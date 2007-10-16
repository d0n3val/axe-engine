/**
* @file
* Functions to conmfigure class access
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      28 May 2004
*/
#include "axsc_stdafx.h"

/**
* Register a class type
*/
AXSC_API int axsc_begin_register_class( const char* name, size_t size, bool type )
{
  // check params
  AXE_ASSERT( NULL != name && 0 != size );

  // check current state
  AXE_ASSERT( state.current_registering_class.is_empty() );
  AXE_ASSERT( NULL != state.engine );
  AXE_ASSERT( AXSC_EXEC_STATE_INIT == state.execution_state );

  int res;
  if( type == false )
  {
    res = state.engine->RegisterObjectType( name, (int) size, asOBJ_CLASS );
  }
  else
  {
    res = state.engine->RegisterObjectType( name, (int) size, asOBJ_PRIMITIVE );
  }

  check_return_value( res );

  state.current_registering_class = name;

  return( AXE_TRUE );
}

/**
* Register a class property
*/
AXSC_API int axsc_register_property( const char* declaration, int offset )
{
  // check params
  AXE_ASSERT( NULL != declaration && offset >= 0 );

  // check current state
  AXE_ASSERT( false == state.current_registering_class.is_empty() );

  int res = state.engine->RegisterObjectProperty( state.current_registering_class, declaration, offset );
  check_return_value( res );

  return( AXE_TRUE );
}

/**
* Register class method
*/
AXSC_API int axsc_register_method( const char* declaration, asUPtr method, axsc_method_type type )
{
  // check params
  AXE_ASSERT( NULL != declaration );
  AXE_ASSERT( type >= AXSC_METHOD_NORMAL && type < AXSC_METHOD_COUNT );

  // check current state
  AXE_ASSERT( false == state.current_registering_class.is_empty() );

  int res = -1;

  if( type > AXSC_METHOD_NORMAL )
  {
    switch( type )
    {
      case AXSC_METHOD_ADD:
      case AXSC_METHOD_SUB:
      case AXSC_METHOD_MUL:
      case AXSC_METHOD_DIV:
      case AXSC_METHOD_MOD:
      case AXSC_METHOD_EQUAL:
      case AXSC_METHOD_NOTEQUAL:
      case AXSC_METHOD_LESSTHAN:
      case AXSC_METHOD_GREATERTHAN:
      case AXSC_METHOD_LEQUAL:
      case AXSC_METHOD_GEQUAL:
      case AXSC_METHOD_LOGIC_OR:
      case AXSC_METHOD_LOGIC_AND:
      case AXSC_METHOD_BIT_OR:
      case AXSC_METHOD_BIT_AND:
      case AXSC_METHOD_BIT_XOR:
      case AXSC_METHOD_BIT_SLL:
      case AXSC_METHOD_BIT_SRL:
      case AXSC_METHOD_LAST_DUAL:
      case AXSC_METHOD_NEGATE:
        {
          res = state.engine->RegisterObjectBehaviour( 0, (DWORD) type, declaration, method, asCALL_CDECL );
        }

        break;

      default:
        {
          res = state.engine->RegisterObjectBehaviour(
              state.current_registering_class,
              (DWORD) type,
              declaration,
              method,
              asCALL_CDECL_OBJLAST );
        }

        break;
    }
  }
  else
  {
    res = state.engine->RegisterObjectMethod( state.current_registering_class, declaration, method, asCALL_THISCALL );
  }

  check_return_value( res );

  return( AXE_TRUE );
}

/**
* End registering this class
*/
AXSC_API int axsc_end_register_class()
{
  AXE_ASSERT( false == state.current_registering_class.is_empty() );

  state.current_registering_class.clear();
  return( AXE_TRUE );
}

/* $Id: axsc_register_class.cpp,v 1.4 2004/09/20 21:28:13 doneval Exp $ */
