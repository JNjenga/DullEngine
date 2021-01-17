#pragma once

/*
 * Handles api stuff, calls appropriate api in different platforms
 * E.g call appropriate clear and draw functions
 *
 */

#include "dull_engine.h"
#include "colors.h"

namespace DE
{
	struct DE_API Mesh
	{
		int vao_id;
		int vertex_count;
		float x, y;
		float scale;
	};

	DE_API inline void clear(DE::Color &);
	DE_API inline void clear();
	DE_API void init_engine();

	DE_API void set_window_bounds(float xbegin, float ybegin, float xend, float yend);

	DE_API int create_mesh2d(float * vertices, int vsize);
	DE_API int create_mesh2d(float * vertices, int vsize, unsigned int *indices, int isize);
	DE_API void draw_mesh2d(int mesh_id);
	DE_API void draw_mesh2d(Mesh * mesh);

	DE_API void destroy_engine();
}
