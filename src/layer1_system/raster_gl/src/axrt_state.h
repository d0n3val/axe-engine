/**
* @file
* state class include header
* Used to store all data about current library state
*/
#ifndef __AXRT_STATE_H__
  #define __AXRT_STATE_H__

  #include "axrt_stdafx.h"

  #define MAX_DIR_LEN 256

/**
* Viewport + perspective + camera data
*/
struct world
{
  struct _viewport
  {
    int   x, y, width, height;
    bool  init;
    bool exec()
    {
      if( init == true )
      {
        glViewport( (GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height );
        return( true );
      }

      return( false );
    }
  } viewport;

  struct _perspective
  {
    float fov, aspect, z_near, z_far;
    bool  init;
    bool exec()
    {
      if( init == true )
      {
        gluPerspective( (GLfloat) fov, (GLfloat) aspect, (GLfloat) z_near, (GLfloat) z_far );
        return( true );
      }

      return( false );
    }
  } perspective;

  struct _camera
  {
    float pos[3], look[3], up[3];
    bool  init;
    bool exec()
    {
      if( init == true )
      {
        gluLookAt( pos[0], pos[1], pos[2], look[0], look[1], look[2], up[0], up[1], up[2] );
        return( true );
      }

      return( false );
    }
  } camera;
};

/**
* This class stores all data related to the state of the library
*/
class axrt_state : public axe_state
{
  public:
    axrt_state() :
    axe_state()
    {
      lib_id = 'AXRT';
      strcpy_s( lib_name, LIB_NAME_LONG, "Raster" );
      lib_version = 1;
      strcpy_s( default_directory, MAX_DIR_LEN, ".\\" );

      // -----------------------------------------------
      init = false;
      ready_to_draw = false;
      wireframe = false;
      context = NULL;
      rendering_context = NULL;
      font_id = 0;
      wpc_data.viewport.init = false;
      wpc_data.perspective.init = false;
      wpc_data.camera.init = false;
    }

    ~axrt_state()
    {
    }

  public:
    char          default_directory[MAX_DIR_LEN];
    bool          init;
    bool          ready_to_draw;
    bool          wireframe;
    HDC           context;
    HGLRC         rendering_context;
    unsigned int  font_id;
    world         wpc_data;
};
#endif // __AXRT_STATE_H__

/* $Id: axrt_state.h,v 1.1 2004/05/02 16:32:33 doneval Exp $ */
