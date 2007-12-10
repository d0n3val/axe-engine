/**
* @file
* Global definitions used every-where
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @version   1.0
* @date      11 Apr 2004
*/
#ifndef __AXE_DEFS_H__
  #define __AXE_DEFS_H__

/*$1- We always want the assert macro ----------------------------------------*/
  #include "axe_assert.h"

/*$1- Process this .h only once ----------------------------------------------*/
  #pragma once

// ****************************************************************************
// **************************** COMMON ****************************************
// ****************************************************************************

/*$1-  Axe Id ----------------------------------------------------------------*/
  #define AXE_ID  unsigned long

/*$1-  Axe boolean values ----------------------------------------------------*/
  #define AXE_TRUE  1
  #define AXE_FALSE 0

/*$1-  Null just in case -----------------------------------------------------*/
  #ifdef NULL
    #undef NULL
  #endif
  #define NULL  0

// ****************************************************************************
// ***************************** UTILS ****************************************
// ****************************************************************************

/*$1- Deletes a buffer -------------------------------------------------------*/
  #define AXE_RELEASE( x ) \
  {                        \
    if( x != NULL )        \
    {                      \
      delete x;            \
    }                      \
                        \
    x = NULL;              \
  }

/*$1- Deletes an array of buffers --------------------------------------------*/
  #define AXE_RELEASE_ARRAY( x ) \
  {                              \
    if( x != NULL )              \
    {                            \
      delete[] x;                \
    }                            \
                              \
    x = NULL;                    \
  }

/*$1- Frees and object using C style -----------------------------------------*/
  #define AXE_FREE( x ) \
  {                     \
    if( x != NULL )     \
    {                   \
      free( x );        \
    }                   \
                     \
    x = NULL;           \
  }

/*$1- Deletes an COM Object --------------------------------------------------*/
  #define RELEASE_COM( obj ) \
  {                          \
    if( NULL != obj )        \
    {                        \
      obj->Release();        \
      obj = NULL;            \
    }                        \
  }

/*$1- Is num in certain range ------------------------------------------------*/
  #define AXE_IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )

/*$1- get min value ----------------------------------------------------------*/
  #define AXE_MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )

/*$1- get min value ----------------------------------------------------------*/
  #define AXE_MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

/*$1- Convert to bool --------------------------------------------------------*/
  #define AXE_TO_BOOL( a )  ( (a != 0) ? true : false )

/*$1- Swap two values --------------------------------------------------------*/
  template <class VALUE_TYPE> inline void axe_swap ( VALUE_TYPE& a, VALUE_TYPE& b )
  {
    VALUE_TYPE tmp = a; 
    a = b, b = tmp;
  }

#endif // __AXE_DEFS_H__

/* $Id: axe_defs.h,v 1.4 2004/09/20 21:28:08 doneval Exp $ */
