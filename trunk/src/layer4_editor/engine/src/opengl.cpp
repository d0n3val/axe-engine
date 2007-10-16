//-----------------------------------------------------------------------------
// opengl class code
//-----------------------------------------------------------------------------
#include "opengl.h"
#include "axe_raster.h"

#define FONT_SIZE 14

//! Public
opengl*           mopengl;
bool opengl::     active = false;
opengl *opengl::  instance = NULL;

// Constructors ---------------------------------------------------------------
opengl::opengl()
{
  mode_2d = false;
}

// Methods --------------------------------------------------------------------
opengl *opengl::create()
{
  if( active == false )
  {
    instance = new opengl;
    active = true;
  }

  return( instance );
}

/**
* init
* Start Opengl Subsystem, set initial states + viewport
*/
bool opengl::init( HDC Context, const screen_info& screen )
{
  axrt_create_device( Context );

  //! Now fix opengl vars related to screen
  resize_screen( screen );

  //! Clear the screen
  //init_frame();
  //axrt_init_dbg_font( Context, "Arial", 14 );
  // load default font to print
  load_font( Context );

  // reset base display list
  dl_base = -1;

  camera.set_identity();

  return( true );
}

/**
* init_frame
* Clear all relevant buffers
*/
void opengl::init_frame()
{
  axrt_prepare_to_draw();
  console_line = 0;
}

/**
* end_frame
* Draw
*/
void opengl::end_frame()
{
  axrt_draw();
}

/**
* resize_screen
* Adapts viewport and perspective to window size
*/
bool opengl::resize_screen( const screen_info& screen )
{
  axrt_set_viewport( screen.left, screen.top, screen.right, screen.bottom );
  axrt_set_perspective( 45, screen.aspect_ratio, 0.1f, 99999.9f );

  this->screen = screen;
  return( true );
}

/**
* set_camera
* Reads camera matrix and set it up to OpenGL
*/
void opengl::set_camera()
{
  axe_vector3 look;
  axe_vector3 up;
  look.create( 0.0f, 0.0f, 1.0f );
  up.create( 0.0f, 1.0f, 0.0f );
  camera.transform( look );
  camera.rotate( up );

  axe_vector3 pos = camera.get_position();

  axrt_set_view( look.ptr, pos.ptr, up.ptr );
}

/**
* set_wireframe
* Sets OpenGL in wireframe mode
*/
void opengl::set_wireframe( bool value )
{
  axrt_set_wireframe( value );
}

/**
* render_array
* This will send to OpenGL a chunk of points
*/
void opengl::render_array( const float* points, unsigned int num_points )
{
  // Enable vertex array
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, points );

  // Draw it
  glDrawArrays( GL_TRIANGLES, 0, num_points );

  // Disable vertex array
  glDisableClientState( GL_VERTEX_ARRAY );
}

/**
* render_array
* This will send to OpenGL a chunk of points with indices. This means that "points" array have no repeated
* data, and id_list contains a list of vertices id (a table look up into "points") to contruct the triangles
*/
void opengl::render_indexed_array( const float* points, unsigned int num_points, unsigned int* id_list )
{
  // Enable vertex array
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, points );

  // Draw it
  glDrawElements( GL_TRIANGLES, num_points, GL_UNSIGNED_INT, id_list );

  // Disable vertex array
  glDisableClientState( GL_VERTEX_ARRAY );
}

/**
* draw_point
* Simply draw a point specified by a vector
*/
void opengl::draw_point( const axe_vector3& v ) const
{
  glPointSize( 1.0f );
  glBegin( GL_POINTS );
  glVertex3f( v.x, v.y, v.z );
  glEnd();
  glPointSize( 1.0f );
}

/**
* draw_sphere
* Usign OpenGL quadrics paint a sphere of specified radius. Think to use "use_translation" before
* calling "draw_sphere" to put it where you want
*/
void opengl::draw_sphere( const float radius ) const
{
  GLUquadric*   qobj;

  qobj = gluNewQuadric();
  gluQuadricDrawStyle( qobj, GLU_LINE );

  // Render
  glColor3f( 0, 1, 0 );
  gluSphere( qobj, (GLdouble) radius, 10, 10 );
}

/**
* draw_axis
* Will draw a typical Axis, as seen in 3d Studio or such. Apply "use_matrix" before calling it
* to put in the rotation/position you want
*/
void opengl::draw_axis( const float size ) const
{
  axrt_draw_axis( size );
}

/**
*/
void opengl::draw_matrix( const axe_matrix_4x4& matrix ) const
{
  axe_vector3 p0;

  axe_vector3 p1;

  axe_vector3 p2;

  axe_vector3 p3;

  p0.create( 0, 0, 0 );
  matrix.transform( p0 );
  p1.create( 10, 0, 0 );
  matrix.transform( p1 );
  p2.create( 0, 10, 0 );
  matrix.transform( p2 );
  p3.create( 0, 0, 10 );
  matrix.transform( p3 );

  glBegin( GL_LINES );
  glColor3f( (GLfloat) 1.0f, 0, 0 );
  glVertex3fv( p0.ptr );
  glVertex3fv( p1.ptr );
  glColor3f( 0, (GLfloat) 1.0f, 0 );
  glVertex3fv( p0.ptr );
  glVertex3fv( p2.ptr );
  glColor3f( 0, 0, (GLfloat) 1.0f );
  glVertex3fv( p0.ptr );
  glVertex3fv( p3.ptr );
  glColor3f( (GLfloat) 1.0f, (GLfloat) 1.0f, (GLfloat) 1.0f );
  glEnd();
}

/**
* draw_line
* 
*/
void opengl::draw_line( const axe_vector3& v1, const axe_vector3& v2 ) const
{
  glLineWidth( 5 );
  glBegin( GL_LINES );
  glColor3f( (GLfloat) 1.0f, 0.0f, 1.0f );
  glVertex3f( v1.x, v1.y, v1.z );
  glVertex3f( v2.x, v2.y, v2.z );
  glEnd();
  glLineWidth( 1 );
}

/**
* draw_base
* To orientate in the 3D world, this function paints a grid in 3D Studio way
* The grid and the axis are stored in a display list to speed up painting
*/
void opengl::draw_base( const int size )
{
  if( dl_base < 0 )
  {
    dl_base = glGenLists( 1 );
    glNewList( dl_base, GL_COMPILE_AND_EXECUTE );

    // draw_plane here
    glBegin( GL_LINES );
    glColor3f( 0.2f, 0.2f, 0.2f );

    int i;
    for( i = -(size); i <= size; ++i )
    {
      if( (i % 10) == 0 )
      {
        glColor3f( 1.0f, 1.0f, 1.0f );
      }

      glVertex3i( size, 0, i );
      glVertex3i( -size, 0, i );
      if( (i % 10) == 0 )
      {
        glColor3f( 0.2f, 0.2f, 0.2f );
      }
    }

    for( i = -(size); i <= size; ++i )
    {
      if( (i % 10) == 0 )
      {
        glColor3f( 1.0f, 1.0f, 1.0f );
      }

      glVertex3i( i, 0, size );
      glVertex3i( i, 0, -size );
      if( (i % 10) == 0 )
      {
        glColor3f( 0.2f, 0.2f, 0.2f );
      }
    }

    glEnd();

    glLineWidth( 5 );
    draw_axis( 10 );
    glLineWidth( 1 );

    glColor3f( (GLfloat) 1.0f, (GLfloat) 1.0f, (GLfloat) 1.0f );

    glEndList();
  }
  else
  {
    glCallList( dl_base );
  }
}

/**
* use_matrix
* Will read a matrix and multiply it with actual matrix. Before is saved previous OpenGL matrix state
* Remember to use "stop_matrix()" after sending the vertices
*/
void opengl::use_matrix( axe_matrix_4x4& m )
{
  glPushMatrix();
  glLoadIdentity();
  glMultMatrixf( m.ptr );
}

/**
* use_translation
* Simply translate an Object in the space
* Remember to use "stop_matrix()" after sending the vertices
*/
void opengl::use_translation( const axe_vector3& v )
{
  glPushMatrix();
  glTranslatef( v.x, v.y, v.z );
}

/**
* stop_matrix
* Will reload a previous saved OpenGL matrix state
*/
void opengl::stop_matrix()
{
  glPopMatrix();
}

/**
* load_font
* Simple function that use a win opegl extension to load directly a windows font like a texture and store it
* in a display list. Display list indices are exactly the char codes. In this way we can print text directly
*/
bool opengl::load_font( HDC Context )
{
  BOOL  result;

  // Create the display list
  font_id = glGenLists( 96 );

  // Create the font
  HFONT hfont;
  hfont = CreateFont(
      FONT_SIZE,                    // Height Of Font
      0,                            // Width Of Font
      0,                            // Angle Of Escapement
      0,                            // Orientation Angle
      0,                            // Font Weight
      FALSE,                        // Italic
      FALSE,                        // Underline
      FALSE,                        // Strikeout
      ANSI_CHARSET,                 // Character Set Identifier
      OUT_DEFAULT_PRECIS,
      CLIP_DEFAULT_PRECIS,
      PROOF_QUALITY,
      FF_DONTCARE | DEFAULT_PITCH,  // Family And Pitch
      "Arial" );                    // Font Name

  // Selects The Font We Want
  SelectObject( Context, hfont );

  // Builds 96 Characters Starting At Character 32
  result = wglUseFontBitmaps( Context, 32, 96, font_id );

  if( result == FALSE )
  {
    AXE_ERROR( "Could not use OpenGL font" );
    return( false );
  }

  // Erase the font
  DeleteObject( hfont );

  //! all ok
  return( true );
}

/**
* print_console
* This prints the top left data that you can print via "mengine->msg(LOW, "hello world");"
*/
void opengl::print_console( const char* sText )
{
  //! set white color
  glColor3f( (GLfloat) 1.0f, (GLfloat) 1.0f, (GLfloat) 1.0f );

  //! print it in 2D
  enter_2d_mode();

  /*
	int	line = MAX(0, mengine->current_msg_line - MAX_MSG_PRINT);
	int i = 1;

	for(; line<mengine->current_msg_line; ++line) {
		glRasterPos2i(5, mengine->screen_rect.bottom-(i*FONT_SIZE));
		glListBase(font_id - 32);
		glCallLists((GLsizei) strlen(mengine->messages[line]), GL_UNSIGNED_BYTE, mengine->messages[line]);
		++i;
	}
	*/
  glRasterPos2i( 5, screen.bottom - (++console_line * FONT_SIZE) );
  glListBase( font_id - 32 );
  glCallLists( (GLsizei) strlen(sText), GL_UNSIGNED_BYTE, sText );

  left_2d_mode();
}

/**
* enter_2d_mode
* Sets OpenGL to print in 2D screen. Remember to use left_2d_mode afterwards
*/
void opengl::enter_2d_mode()
{
  if( mode_2d == true )
  {
    return;
  }

  // we don't like this id 2D mode
  glDisable( GL_DEPTH_TEST );
  glDisable( GL_CULL_FACE );

  //! push projection and clear
  glMatrixMode( GL_PROJECTION );
  glPushMatrix();
  glLoadIdentity();

  //! 2D mode
  gluOrtho2D( 0, (GLfloat) screen.right, 0, (GLfloat) screen.bottom );

  //! push model and clear
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();

  //!push LIST_BIT
  glPushAttrib( GL_LIST_BIT );

  mode_2d = true;
}

/**
* left_2d_mode
* Sets OpenGL to 3D mode
*/
void opengl::left_2d_mode()
{
  if( mode_2d == false )
  {
    return;
  }

  // reget 3d modes
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );
  glEnable( GL_CULL_FACE );
  glCullFace( GL_BACK );

  //! pop projection
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();

  //! pop model
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();

  //! pop LIST_BIT
  glPopAttrib();

  mode_2d = false;
}

/**
* deinit
* Delete windows OpenGL rendering context
*/
bool opengl::deinit()
{
  axrt_release();

  /*
  //! Free rendering context
  if( rendering_context != NULL )
  {
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( rendering_context );
    rendering_context = NULL;
  }
  */
  return( true );
}

// Destructor -----------------------------------------------------------------
opengl::~opengl()
{
  active = false;
}
