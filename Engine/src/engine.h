#pragma once

/*
 * Handles api stuff, calls appropriate api in different platforms
 * E.g call appropriate clear and draw functions
 *
 */

#include "dull_engine.h"
#include <GL/glew.h>
#include "colors.h"
#include "ogl_api.h"

namespace DE
{
	struct DE_API Mesh
	{
		int vao_id;
		int texture_id;
		int vertex_count;
		float x, y;
		float scale;
	};

	DE_API inline void clear(DE::Color & color){ DE::GL::clear(color); }
	DE_API inline void clear(){ DE::GL::clear(); }
	DE_API void init_engine();

	DE_API void set_window_bounds(float xbegin, float ybegin, float xend, float yend);

	DE_API int create_mesh2d(float * vertices, int vsize);
	DE_API int create_mesh2d(float * vertices, int vsize, unsigned int *indices, int isize);
	DE_API int create_mesh(DE::GL::vao_data_t vao);
	DE_API int create_texture(const char * path);

	DE_API void draw_mesh2d(int mesh_id);
	DE_API void draw_mesh2d(Mesh * mesh);

	DE_API void destroy_engine();
}
