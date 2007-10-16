/**
* @file
* Engine singleton
* @author    Ricard Pillosu <d0n3val\@gmail.com>
* @date      11 Sep 2004
*/
#include "axen_stdafx.h"
#include "axen_window.h"
#include "axen_control.h"
#include "axe_file_system.h"

#include "opengl.h"
extern opengl*  mopengl;

/*$1- Global instance of this singleton --------------------------------------*/
axen_engine*  engine = NULL;

/*$1- Singleton stuff --------------------------------------------------------*/
bool axen_engine::          active = false;
axen_engine *axen_engine::  instance = NULL;

/*$1- Constructor & Destructor -----------------------------------------------*/

/**
* Constructor
*/
axen_engine::axen_engine()
{
  timer_id = axtm_create();
  window = NULL;
  input = NULL;
}

/**
* Destructor
*/
axen_engine::~axen_engine()
{
  AXE_RELEASE( input );
  AXE_RELEASE( window );
  active = false;
}

/*$1- Singleton stuff --------------------------------------------------------*/

/**
* Singleton creator
*/
axen_engine *axen_engine::create()
{
  if( active == false )
  {
    instance = new axen_engine;
    active = true;
  }

  return( instance );
}

/*$1- Methods ----------------------------------------------------------------*/

/**
* Init
*/
bool axen_engine::init()
{
  window = axen_window::create();
  AXE_ASSERT( NULL != window );

  input = axen_control::create();
  AXE_ASSERT( NULL != input );

  virtual_camera.set_identity();

  cam.set_identity();

  return( true );
}

/**
* Init after window starts
*/
bool axen_engine::start_window()
{
  HWND        win = window->get_window();
  HINSTANCE   instance = window->get_instance();
  HDC         device = engine->get_window()->get_device();
  screen_info screen = engine->get_window()->get_screen_size();

  input->init( win, instance );
  mopengl->init( device, screen );
  load_model();

  return( true );
}

/**
* Loop each window iteration
*/
bool axen_engine::loop_window()
{
  float secs = axtm_elapsed_from_mark( timer_id );
  input->update( secs );

  // Clear buffers
  mopengl->set_camera();
  mopengl->init_frame();

  check_keys();

  // Set camera
  mopengl->draw_base( 100 );

  draw_model();

  // show result to user
  mopengl->end_frame();


  return( true );
}

/**
* Window closed
*/
bool axen_engine::end_window()
{
  input->done();
  mopengl->deinit();
  axfs_destroy(id_file, AXE_FALSE);
  return( true );
}

/**
* Exit engine
*/
void axen_engine::exit()
{
  if( window )
  {
    window->end();
  }
}

/**
* Log
*/
void axen_engine::log( const axe_string& str )
{
  AXE_INFO( (const char*) str );
}

/**
* Log
*/
#define EVENT_W_KEY   17
#define EVENT_A_KEY   30
#define EVENT_S_KEY   31
#define EVENT_D_KEY   32
#define EVENT_C_KEY   46
#define EVENT_SB_KEY  57
#define EVENT_UP_KEY   200 
#define EVENT_DOWN_KEY 208 
#define EVENT_LEFT_KEY 203 
#define EVENT_RIGHT_KEY 205 

void axen_engine::check_keys()
{
  
  axe_vector3 a;
  a.create(-22.0f, 22.0f, -100.0f);
  mopengl->camera.set_identity();

  // --------------------------
  bool  forward = input->is_key_down( EVENT_W_KEY );
  bool  left = input->is_key_down( EVENT_A_KEY );
  bool  right = input->is_key_down( EVENT_D_KEY );
  bool  backwards = input->is_key_down( EVENT_S_KEY );
  bool  up = input->is_key_down( EVENT_SB_KEY );
  bool  down = input->is_key_down( EVENT_C_KEY );
  bool  arrow_up = input->is_key_down( EVENT_UP_KEY );
  bool  arrow_down = input->is_key_down( EVENT_DOWN_KEY );
  bool  arrow_left = input->is_key_down( EVENT_LEFT_KEY );
  bool  arrow_right = input->is_key_down( EVENT_RIGHT_KEY );

  float x = ( right ? -1.0f : 0.0f );
  x += ( left ? 1.0f : 0.0f );

  float y = ( up ? 1.0f : 0.0f );
  y += ( down ? -1.0f : 0.0f );

  float z = ( forward ? 1.0f : 0.0f );
  z += ( backwards ? -1.0f : 0.0f );

  float pitch = ( arrow_up ? -0.05f : 0.0f );
  pitch += ( arrow_down ? 0.05f : 0.0f );

  float yaw = ( arrow_right ? -0.05f : 0.0f );
  yaw += ( arrow_left ? 0.05f : 0.0f );

  int               mx = 0;
  int               my = 0;

  input->get_mouse_steering( &mx, &my );
  axe_vector3 opos = virtual_camera.get_position();

  if( mx || my )
  {
    pitch += (float) my / 300.0f;
    yaw += (float) -mx / 300.0f; 
  }

  if ( pitch || yaw )
  {
    cam.pitch += pitch;
    cam.yaw += yaw;

    if (cam.pitch > HALF_PI)
    {
      cam.pitch = HALF_PI;
    }

    if (cam.pitch < -HALF_PI)
    {
      cam.pitch = -HALF_PI;
    }

    cam.canonize();

    virtual_camera.set_rotation(cam);
  }

  if( x || y || z )
  {
    // --
    axe_vector3 pos;
    pos.create(x,y,z);
    virtual_camera.transform(pos);
    virtual_camera.set_position(pos);
  } 
  else
  {
    virtual_camera.set_position(opos);
  }

  // --
  axe_matrix_4x4 m(virtual_camera);
  m.transpose();
  mopengl->use_matrix(m);
  //mopengl->draw_axis(10);
  mopengl->stop_matrix();
  

  //mopengl->draw_matrix(virtual_camera);
  mopengl->camera.create(virtual_camera);

  /*// --
  axe_string  s;
  s.create( "%0.3f %0.3f %0.3f %0.3f", virtual_camera.d00, virtual_camera.d10, virtual_camera.d20, virtual_camera.d30);
  mopengl->print_console( s );
  s.create( "%0.3f %0.3f %0.3f %0.3f", virtual_camera.d01, virtual_camera.d11, virtual_camera.d21, virtual_camera.d31);
  mopengl->print_console( s );
  s.create( "%0.3f %0.3f %0.3f %0.3f", virtual_camera.d02, virtual_camera.d12, virtual_camera.d22, virtual_camera.d32);
  mopengl->print_console( s );
  s.create( "%0.3f %0.3f %0.3f %0.3f", virtual_camera.d03, virtual_camera.d13, virtual_camera.d23, virtual_camera.d33);
  mopengl->print_console( s );
  s.create( "x:%f y:%f z:%f pitch:%f yawn:%f", x,y,z,cam.pitch,cam.yaw);
  mopengl->print_console( s );
  */
}

void axen_engine::load_model()
{
  const char *dir = axfs_get_current_dir();
  id_file = axfs_create("..\\..\\..\\data\\xyz.m2");

  char const * pData = (const char*)axfs_get_data(id_file);
  memcpy(&header, pData, sizeof(ModelHeader));

  
  /*int *globalSequences;

  if (header.nGlobalSequences) {
    globalSequences = new int[header.nGlobalSequences];
    memcpy(globalSequences, (pData + header.ofsGlobalSequences), header.nGlobalSequences * 4);
  }
  */

  origVertices = (ModelVertex*)(pData + header.ofsVertices);
  vertices = new axe_vector3[header.nVertices];

  for (size_t i=0; i<header.nVertices; i++) {
    vertices[i] = origVertices[i].pos;
  }

  // indices - allocate space, too
  ModelView *view = (ModelView*)(pData + header.ofsViews);

  // Indices,  Triangles
  uint16 *indexLookup = (uint16*)(pData + view->ofsIndex);
  uint16 *triangles = (uint16*)(pData + view->ofsTris);
  nIndices = view->nTris;
  indices = new uint16[nIndices];
  for (size_t i = 0; i<nIndices; i++) {
    indices[i] = indexLookup[triangles[i]];
  }

  // render ops
	ModelGeoset *ops = (ModelGeoset*)(pData + view->ofsSub);
	ModelTexUnit *tex = (ModelTexUnit*)(pData + view->ofsTex);

	for (size_t j = 0; j<view->nTex; j++) {
		size_t geoset = tex[j].op;
		
		pass.geoset = (int)geoset;

		pass.indexStart = ops[geoset].istart;
		pass.indexCount = ops[geoset].icount;
		pass.vertexStart = ops[geoset].vstart;
		pass.vertexEnd = pass.vertexStart + ops[geoset].vcount;
	}

}

void axen_engine::draw_model()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glBegin(GL_TRIANGLES);
	for (size_t k = 0, b=pass.indexStart; k<pass.indexCount; k++,b++) {
		uint16 a = indices[b];
	  //glVertex3fv(vertices[a].ptr);
		glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);
	}
	glEnd();
}


/* $Id: axen_engine.cpp,v 1.1 2004/09/20 21:28:14 doneval Exp $ */
