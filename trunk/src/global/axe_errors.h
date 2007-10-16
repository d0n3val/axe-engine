/**
* @file
* Error mangment for libraries
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @version   1.0
* @date      12 Apr 2004
*/
#ifndef __AXE_ERRORS_H__
  #define __AXE_ERRORS_H__

/*$1- Process this.h only once -----------------------------------------------*/
  #pragma once

/*$1- Shortcut definitions ---------------------------------------------------*/
  #define AXE_SET_ERROR( error_num )  state.set_error( error_num, __FILE__, __LINE__ );

  #define AXE_CHECK_ERROR( expr, error_num ) \
  if( !(expr) )                              \
  {                                          \
    AXE_SET_ERROR( error_num );              \
    return( 0 );                             \
  }

  #define AXE_RETURN_ON_FALSE( expr ) \
  if( !(expr) )                       \
  {                                   \
    return( 0 );                      \
  }                                      

  #ifdef _DEBUG
    #define AXE_CHECK_DBG_ERROR( expr, error_num ) \
  if( !(expr) )                                    \
  {                                                \
    AXE_ASSERT( AXE_FALSE );                       \
    AXE_SET_ERROR( error_num );                    \
    return( 0 );                                   \
  }                                                     

    #define AXE_DBG_RETURN_ON_FALSE( expr ) \
    if( !(expr) )                           \
    {                                       \
        AXE_ASSERT( false );                \
        return( 0 );                        \
    }                                       \

  #else
    #define AXE_CHECK_DBG_ERROR( expr, error_num )  __noop
  #endif

/*$1- Basic error messages. Warning! mantain the array and the anum in sync --*/
  #define AXE_NUM_BASIC_ERROR_MSG 10

static const char*  basic_error_messages[AXE_NUM_BASIC_ERROR_MSG] =
{
  "No error",                     // 0
  "Function not implemented",     // 1
  "Unknown error number",         // 2
  "Could not 'get' state",        // 3
  "Could not 'set' state",        // 4
  "Bad arguments",                // 5
  "Unknown AXE_ID",               // 6
  "Bad error callback function",  // 7
  "Unknown error",                // 9
  "Object not initialized",       // 10
};

enum AXE_BASIC_ERROR_MSG
{
  AXE_ERROR_MSG_NO_ERROR                    = 0,
  AXE_ERROR_MSG_FUNCTION_NOT_IMPLEMENTED,
  AXE_ERROR_MSG_UNKNOWN_ERROR_NUMBER,
  AXE_ERROR_MSG_COULD_NOT_GET_STATE,
  AXE_ERROR_MSG_COULD_NOT_SET_STATE,
  AXE_ERROR_MSG_BAD_ARGUMENTS,
  AXE_ERROR_MSG_UNKNOWN_ID,
  AXE_ERROR_MSG_BAD_ERROR_CALLBACK_FUNCTION,
  AXE_ERROR_MSG_UNKNOW_ERROR,
  AXE_ERROR_MSG_OBJECT_NOT_INITIALIZED,
  AXE_BASIC_ERROR_MSG_COUNT,
};
#endif // __AXE_ERRORS_H__

/* $Id: axe_errors.h,v 1.6 2004/09/05 21:35:04 ilgenio Exp $ */
