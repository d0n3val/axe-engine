/**
* @file
* Get directly a pure pseudo-randim number
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      18 Apr 2004
*/
#include "axrd_stdafx.h"

/**
* Generate a float [0..1]
*/
AXRD_API float axrd_pure_get_float() {
  return( (float) state.randomizer.get_double() );
}

/**
* Generate a double [0..1]
*/
AXRD_API double axrd_pure_get_double() {
  return( state.randomizer.get_double() );
}

/**
* Generate an int [MIN_INT..MAX_INT]
*/
AXRD_API int axrd_pure_get_int() {
  return( (int) state.randomizer.get_long() );
}

/**
* Generate an unsigned int [0..MAX_UINT]
*/
AXRD_API unsigned int axrd_pure_get_uint() {
  return( (unsigned int) state.randomizer.get_ulong() );
}

/**
* Generate a long [MIN_LONG..MAX_LONG]
*/
AXRD_API long axrd_pure_get_long() {
  return( state.randomizer.get_long() );
}

/**
* Generate an unsigned long [0..MAX_ULONG]
*/
AXRD_API unsigned long axrd_pure_get_ulong() {
  return( state.randomizer.get_ulong() );
}

/* $Id: axrd_pure_get.cpp,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
