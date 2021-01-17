/*
 * This header handles opengl calls.
 * e.g create_shader, create_vao, create_vbo, enable stuff etc
 *
 */


#pragma once
#include "dull_engine.h"
#include "colors.h"
#include <glm/glm.hpp> 

#include <unordered_map>

namespace DE
{
	namespace GL
	{
		struct shader_program_t
		{
			unsigned int shader_id;
			std::unordered_map<const char *, int> uniforms;
		};

		void init_opengl();
		DE_API inline void clear();
		DE_API inline void clear(DE::Color & color);

		// Shader stuff
		shader_program_t * create_shader(const char * fsource,
				const char * vsource);

		int reload_shader(int shader_id,
				int shader_type, const char * source);

		int get_uniform_loc(shader_program_t *shader, const char * name);
		int setu_float(const char * name, float value);
		int setu_int(shader_program_t * shader, const char * name, int value);
		int setu_mat4(shader_program_t * shader, const char * name, glm::mat4 value);

		int create_vao(float vertices[], int vsize);
		int create_vao(float vertices[], int vsize, unsigned int indices[], int isize);
		void draw_mesh(int vao_id, int vertex_count);
		void draw_mesh(int vao_id, int mode, int vertex_count);
		void draw_primitive( int vao_id, int mode, int vertex_count);
		int glCheckError_(const char * file, int line);
}
}
