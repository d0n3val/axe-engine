#pragma warning( disable : 4201 )

/**
* @file
* 
* @author    Carlos Fuentes
* @date      04 Jul 2004
*/
#ifndef __AXE_RASTER_H__
  #define __AXE_RASTER_H__

/*$1- Main definitions for Axe libs ------------------------------------------*/
  #include "axe_defs.h"

/*$1- DLL proper function prefix ---------------------------------------------*/
  #ifdef _USRDLL
    #define AXRT_API  extern "C"__declspec( dllexport )
    #pragma message( "Compiling Axe 'raster' ..." )
  #else
    #define AXRT_API  extern "C"__declspec( dllimport )
    #pragma message( "Using Axe 'raster' ..." )

/*$1- Automatic .lib link ----------------------------------------------------*/
    #ifndef AXRT_NO_AUTOLINK
      #pragma comment( lib, "axe_raster.lib" )
    #endif
  #endif

/*$1-States for this lib -----------------------------------------------------*/
enum axrt_states
{
  AXRT_VERSION      = 1,
  AXRT_LIBRARY_NAME,
  AXRT_LIBRARY_ID,
  AXRT_DEBUG_MODE,
  AXRT_LAST_ERROR,
  AXRT_STATE_COUNT
};

/*$1- Standard Outputs for errors and dumps ----------------------------------*/
enum axrt_outputs
{
  AXRT_NONE         = 1,
  AXRT_OUTPUT_DEBUG,
  AXRT_MESSAGE_BOX,
  AXRT_DBG_MSG_BOX,
  AXRT_FILE,
  AXRT_BREAKPOINT,
};

/*$1- Mesh related data types ------------------------------------------------*/
enum axrt_mesh_data
{
  AXRT_MESH_DATA_POSITION     = 0,
  AXRT_MESH_DATA_TEXTURE_COORD,
  AXRT_MESH_DATA_DIFFUSE,
  AXRT_MESH_DATA_COUNT
};

/*$1- Mesh primitive types ---------------------------------------------------*/
enum axrt_mesh_primitive_types
{
  AXRT_PRIMITIVE_POINTLIST    = 1,
  AXRT_PRIMITIVE_LINELIST,
  AXRT_PRIMITIVE_LINESTRIP,
  AXRT_PRIMITIVE_TRIANGLELIST,
  AXRT_PRIMITIVE_TRIANGLESTRIP,
  AXRT_PRIMITIVE_TRIANGLEFAN,
};

/*$1- Mesh types -------------------------------------------------------------*/
enum axrt_mesh_type
{
  AXRT_MESH_STATIC            = 0,
  AXRT_MESH_SOFTWARE_SKINING  = 0x002 | 0x040 | 101 // See direct3d FVF and index formats
};

/*$1- Matrix transform types -------------------------------------------------*/
enum axrt_transform_types
{
  AXRT_MATRIX_VIEW            = 2,
  AXRT_MATRIX_PROJECTION      = 3,
  AXRT_MATRIX_WORLD           = 256,
  AXRT_MATRIX_TEXTURE0        = 16,
};

/*$1- Mesh creation structure ------------------------------------------------*/
struct axrt_mesh_params
{
  unsigned int  max_index;
  unsigned int  max_vertices;
  union
  {
    struct
    {
      bool  has_position;
      bool  has_texture_coord;
      bool  has_diffuse;
    };
    bool  has_data[AXRT_MESH_DATA_COUNT];
  };

  axrt_mesh_primitive_types primitive_type;
  axrt_mesh_type            type;

  axrt_mesh_params()
  {
    max_index = max_vertices = 0;
    for( int i = 0; i < AXRT_MESH_DATA_COUNT; ++i )
    {
      has_data[i] = AXE_FALSE;
    }

    primitive_type = AXRT_PRIMITIVE_TRIANGLELIST;
    type = AXRT_MESH_STATIC;
  }
};

class axrt_3dmesh;
class axrt_texture;
typedef const axrt_3dmesh*   mesh3d_id;
typedef const axrt_texture* texture_id;

/** @example axwd_test.cpp */
extern "C"
{

  /*$1- axrt_raster_main.cpp -------------------------------------------------*/
  AXRT_API unsigned int axrt_get( const int query_state );
  AXRT_API unsigned int axrt_set( const int query_state, const unsigned int new_value );
  AXRT_API const char*  axrt_get_error_message( const unsigned int error_number );
  AXRT_API int          axrt_set_error_callback( void (*error_callback) (int, const char*, long) );

  /*$1- axrt_initialization.cpp ----------------------------------------------*/
  AXRT_API bool axrt_create_device( HWND window_handle, bool windowed );  
  AXRT_API bool axrt_release(void);

  /*$1- axrt_state_management.cpp --------------------------------------------*/
  AXRT_API bool axrt_set_transform( axrt_transform_types type, float* matrix );
  AXRT_API bool axrt_set_viewport( short x, short y, short width, short height, float min_z, float max_z );
  AXRT_API bool axrt_set_projection( float fov, float aspect, float z_near, float z_far );
  AXRT_API bool axrt_set_world_matrix( float* matrix );
  AXRT_API bool axrt_set_view( float eye[3], float at[3], float up[3] );

  /*$1- axrt_mesh_management.cpp ---------------------------------------------*/
  AXRT_API texture_id axrt_create_texture(const void* file_memory, unsigned int file_size);
  AXRT_API mesh3d_id  axrt_create_3dmesh( const axrt_mesh_params& params );
  AXRT_API int        axrt_set_vertex_data( mesh3d_id       mesh,
                                            axrt_mesh_data  type,
                                            const void*     data_ptr,
                                            unsigned int    data_size );
  AXRT_API int        axrt_set_index_data( mesh3d_id mesh, const void* data_ptr, unsigned int data_size );
  AXRT_API int        axrt_set_texture(mesh3d_id mesh, texture_id texture, unsigned int stage = 0);
  AXRT_API int        axrt_register_mesh( mesh3d_id mesh );
  AXRT_API int        axrt_render_mesh( mesh3d_id mesh );
  AXRT_API int        axrt_present_scene( void );
} // extern "C"
#endif // __AXE_RASTER_H__

/* $Id: axe_raster.h,v 1.1 2004/07/27 21:19:28 ilgenio Exp $ */
