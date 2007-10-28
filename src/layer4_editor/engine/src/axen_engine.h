/**
* @file
* Engine singleton
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      11 Sep 2004
*/
#ifndef __AXEN_ENGINE_H__
  #define __AXEN_ENGINE_H__

  #include "axen_stdafx.h"
  #include "opengl.h"
  #include "modelheaders.h"
  #include "opengl.h"

/*$1- Back declarations ------------------------------------------------------*/
class axen_window;
class axen_control;
class axe_string;
class opengl;
struct ModelVertex;
struct ModelHeader;

extern opengl* mopengl;

/**
* Engine singleton
*/
class axen_engine
{

  /*$1- Singleton stuff ------------------------------------------------------*/
  public:
    static axen_engine*   create();
    ~axen_engine();
  private:
    static bool           active;
    static axen_engine*   instance;
    axen_engine();

  /*$1- Methods --------------------------------------------------------------*/
  public:
    inline axen_window* get_window()
    {
      AXE_ASSERT( window != NULL );
      return( window );
    }

    inline const axen_window* get_window() const
    {
      AXE_ASSERT( window != NULL );
      return( window );
    }

    inline axen_control* get_input()
    {
      AXE_ASSERT( input != NULL );
      return( input );
    }

    inline const axen_control* get_input() const
    {
      AXE_ASSERT( input != NULL );
      return( input );
    }

    bool  init();
    bool  start_window();
    bool  loop_window();
    bool  end_window();
    void  exit();

    void  check_keys();
    void  load_model();
    void  draw_model();

    /*$1- Log ----------------------------------------------------------------*/
    void  log( const axe_string& str );

    /*$1- Function to call on start and end ----------------------------------*/
    axe_string  function_on_start;
    axe_string  function_on_end;

  /*$1- Properties -----------------------------------------------------------*/
  private:
    axen_window*      window;
    axen_control*     input;
    AXE_ID            timer_id;
    axe_euler_angles  cam;
    axe_matrix_4x4    virtual_camera;
    ModelHeader       header;
    ModelVertex*      origVertices;
    size_t            nIndices;
    uint16*           indices;
    ModelRenderPass   pass;
    axe_vector3*      vertices;
    unsigned int*     textures;

    AXE_ID            id_file;
};
#endif // __AXEN_ENGINE_H__

/* $Id: axen_engine.h,v 1.1 2004/09/20 21:28:14 doneval Exp $ */
