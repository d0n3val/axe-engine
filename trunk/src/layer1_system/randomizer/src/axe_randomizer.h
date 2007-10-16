/**
* @file
* Axe 'randomizer' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  21/12/2003 
*/
#ifndef __AXE_RANDOMIZER_H__
  #define __AXE_RANDOMIZER_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXRD_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Randomizer' ..." )
  #else
    #define AXRD_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Randomizer' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXRD_NO_AUTOLINK
      #pragma comment( lib, "axe_randomizer.lib" )
    #endif
  #endif

/*$1-  Number of random number pool ------------------------------------------*/
  #define AXRD_BUFFER_SIZE  500

/*$1- States for this lib ----------------------------------------------------*/
enum axrd_states
{
  AXRD_VERSION      = 1,
  AXRD_LIBRARY_NAME,
  AXRD_LIBRARY_ID,
  AXRD_DEBUG_MODE,
  AXRD_LAST_ERROR,
  AXRD_STATE_COUNT,
};

/** @example axrd_test.cpp */
extern "C"
{

  /*$1- axrd_randomizer.cpp --------------------------------------------------*/
  AXRD_API unsigned int axrd_get( const int query_state );
  AXRD_API unsigned int axrd_set( const int query_state, const unsigned int new_value );
  AXRD_API const char*  axrd_get_error_message( const unsigned int error_number );
  AXRD_API int          axrd_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axrd_init.cpp --------------------------------------------------------*/
  AXRD_API void           axrd_set_seed( const unsigned long seed );
  AXRD_API unsigned long  axrd_get_seed();

  /*$1- axrd_data.cpp --------------------------------------------------------*/
  AXRD_API int  axrd_set_data( const unsigned long seed, const unsigned long data[AXRD_BUFFER_SIZE] );
  AXRD_API int  axrd_get_data( unsigned long& seed, unsigned long data[AXRD_BUFFER_SIZE] );

  /*$1- axrd_pure_get.cpp ----------------------------------------------------*/
  AXRD_API float          axrd_pure_get_float();  // [0..1]
  AXRD_API double         axrd_pure_get_double(); // [0..1]
  AXRD_API int            axrd_pure_get_int();    // [MIN_INT..MAX_INT]
  AXRD_API unsigned int   axrd_pure_get_uint();   // [0..MAX_UINT]
  AXRD_API long           axrd_pure_get_long();   // [MIN_LONG..MAX_LONG]
  AXRD_API unsigned long  axrd_pure_get_ulong();  // [0..MAX_ULONG]

  /*$1- axrd_get.cpp ---------------------------------------------------------*/
  AXRD_API float          axrd_get_float( const unsigned long pos = -1 );   // [0..1]
  AXRD_API double         axrd_get_double( const unsigned long pos = -1 );  // [0..1]
  AXRD_API int            axrd_get_int( const unsigned long pos = -1 );     // [MIN_INT..MAX_INT]
  AXRD_API unsigned int   axrd_get_uint( const unsigned long pos = -1 );    // [0..MAX_UINT]
  AXRD_API long           axrd_get_long( const unsigned long pos = -1 );    // [MIN_LONG..MAX_LONG]
  AXRD_API unsigned long  axrd_get_ulong( const unsigned long pos = -1 );   // [0..MAX_ULONG]

  /*$1- axrd_get_min_max.cpp -------------------------------------------------*/
  AXRD_API float          axrd_get_float_min_max( const float min, const float max, const unsigned long pos = -1 );
  AXRD_API double         axrd_get_double_min_max( const double min, const double max, const unsigned long pos = -1 );
  AXRD_API int            axrd_get_int_min_max( const int min, const int max, const unsigned long pos = -1 );
  AXRD_API unsigned int   axrd_get_uint_min_max( const unsigned int  min,
                                                 const unsigned int  max,
                                                 const unsigned long pos = -1 );
  AXRD_API long           axrd_get_long_min_max( const long min, const long max, const unsigned long pos = -1 );
  AXRD_API unsigned long  axrd_get_ulong_min_max( const unsigned long min,
                                                  const unsigned long max,
                                                  const unsigned long pos = -1 );

  /*$1- axrd_jitter.cpp ------------------------------------------------------*/
  AXRD_API void axrd_jitter( float& value, const float jitter, const long pos = -1 );
  AXRD_API void axrd_jitter_array( float* values, const int values_count, const float jitter, const long pos = -1 );

  /*$1-axrd_dice.cpp ---------------------------------------------------------*/
  AXRD_API int  axrd_roll( const int sides, const int dice_count, const long pos = -1 );
  AXRD_API int  axrd_percent( const int percent, const long pos = -1 );

/*$1- macros for logic versions ----------------------------------------------*/
  #define axrd_logic_get_float()                    axrd_get_float( __LINE__ )
  #define axrd_logic_get_float_min_max( min, max )  axrd_get_float_min_max( min, max, __LINE__ )
  #define axrd_logic_get_double()                   axrd_get_double( __LINE__ )
  #define axrd_logic_get_double_min_max()           axrd_get_double_min_max( min, max, __LINE__ )
  #define axrd_logic_get_int()                      axrd_get_int( __LINE__ )
  #define axrd_logic_get_int_min_max( min, max )    axrd_get_int_min_max( min, max, __LINE__ )
  #define axrd_logic_get_uint()                     axrd_get_uint( __LINE__ )
  #define axrd_logic_get_uint_min_max( min, max )   axrd_get_uint_min_max( min, max, __LINE__ )
  #define axrd_logic_get_long()                     axrd_get_long( __LINE__ )
  #define axrd_logic_get_long_min_max()             axrd_get_long_min_max( min, max, __LINE__ )
  #define axrd_logic_get_ulong()                    axrd_get_ulong( __LINE__ )
  #define axrd_logic_get_ulong_min_max()            axrd_get_ulong_min_max( min, max, __LINE__ )
  #define axrd_logic_jitter( value, jitter )        axrd_jitter( value, jitter, __LINE__ )
  #define axrd_logic_jitter_array( values, values_count, jitter ) \
    axrd_jitter_array(                                            \
      values,                                                     \
      values_count,                                               \
      jitter,                                                     \
      __LINE__ )
  #define axrd_logic_roll( sides, dice_count )  axrd_roll( sides, dice_count, __LINE__ )
  #define axrd_logic_percent( percent )         axrd_percent( percent, __LINE__ )
} // extern "C"
#endif // __AXE_RANDOMIZER_H__

/* $Id: axe_randomizer.h,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
