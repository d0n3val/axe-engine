//-----------------------------------------------------------------------------
// opengl class definiton
//-----------------------------------------------------------------------------

#ifndef __OPENGL_H__
#define __OPENGL_H__

//! Libs required
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//! OpenGL
#include "axen_window.h"
#include "axe_math.h"
#include <GL/gl.h>
#include <GL/glu.h>
/*
#include "GLext.h"
*/

/**
 * opengl class
 * All OpenGL stuff goes here
 */
class opengl {
private:
	static bool active;			//< For controlling if this class is active
	static opengl *instance;	//< Static active instance of this singleton
	opengl();					//< Constructor private :)
public:
	static	opengl *create();
	bool	mode_2d, wireframe;
	int		dl_base;
	HGLRC   rendering_context;
	unsigned int font_id;
	screen_info screen;
  int console_line;

	// camera is represented by a matrix. It looks to it's +Z axis
	axe_matrix_4x4	camera;

	// Methods -------------------------------------
	bool init(HDC Context, const screen_info& screen);
	bool deinit();
	bool resize_screen( const screen_info& );
	void init_frame();
  void end_frame();
	void set_camera();

	void enter_2d_mode();
	void left_2d_mode();
	bool load_font(HDC Context);
	void print_console(const char* sText);

	void set_wireframe(bool);

	void draw_matrix(const axe_matrix_4x4& matrix) const;
	void draw_axis(const float size) const;
	void draw_base(const int size);
	void draw_sphere(const float radius) const;
  void draw_line(const axe_vector3& v1, const axe_vector3& v2) const;
	void draw_point(const axe_vector3 &) const;

	void use_matrix(axe_matrix_4x4 &);
	void use_translation(const axe_vector3 &);
	void stop_matrix();

	void render_array(const float *points, unsigned int num_points);
	void render_indexed_array(const float *points, unsigned int num_points, unsigned int *id_list);

	~opengl(); //< the destructor is important here!
};

#endif  /*__OPENGL_H__*/