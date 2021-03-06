/**
* @file
* Axe 'Raster (opengl)' library PUBLIC include header
* @author	  Ricard Pillosu <d0n3val\@gmail.com>
* @version	1.0
* @date		  14 Oct 2007
*/
#ifndef __AXE_RASTER_H__
  #define __AXE_RASTER_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1-  DLL proper function prefix --------------------------------------------*/
  #ifdef _USRDLL
    #define AXRT_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'Raster' library ..." )
  #else
    #define AXRT_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'Raster' library ..." )

/*$1-  Automatic .lib link ---------------------------------------------------*/
    #ifndef AXRT_NO_AUTOLINK
      #pragma comment( lib, "axe_raster.lib" )
    #endif
  #endif

/*$1- States for this lib ----------------------------------------------------*/
enum axrt_states
{
  AXRT_VERSION      = 1,
  AXRT_LIBRARY_NAME,
  AXRT_LIBRARY_ID,
  AXRT_DEBUG_MODE,
  AXRT_LAST_ERROR,
  AXRT_STATE_COUNT,
};

/** @example axrt_test.cpp */
extern "C"
{

  /*$1- axpl_plug_in.cpp -----------------------------------------------------*/
  AXRT_API unsigned int axrt_get( const int query_state );
  AXRT_API unsigned int axrt_set( const int query_state, const unsigned int new_value );
  AXRT_API const char*  axrt_get_error_message( const unsigned int error_number );
  AXRT_API int          axrt_set_error_callback( void (*error_callback) (int, const char*, long) );
  AXRT_API int          axrt_get_int( const int query_state );
  AXRT_API int          axrt_set_int( const int query_state, const int new_value );

  /*$1- axrt_init.cpp --------------------------------------------------------*/
  AXRT_API int  axrt_create_device( HDC context );
  AXRT_API int  axrt_release( void );

  /*$1- axrt_world.cpp -------------------------------------------------------*/
  AXRT_API int  axrt_set_viewport( int x, int y, int width, int height );
  AXRT_API int  axrt_set_perspective( float fov, float aspect, float z_near, float z_far );
  AXRT_API int  axrt_set_view( float look[3], float pos[3], float up[3] );
  AXRT_API int  axrt_prepare_to_draw();
  AXRT_API int  axrt_draw();
  AXRT_API int  axrt_set_wireframe( int wireframe );

  /*$1- axrt_debug_geoms.cpp -------------------------------------------------*/
  AXRT_API int  axrt_draw_axis( float size );

  /*$1- axrt_texture.cpp -----------------------------------------------------*/
  AXRT_API AXE_ID axrt_load_texture( const char* file_name );
} // extern "C"
#endif // __AXE_RASTER_H__

/* $Id: axe_raster.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
