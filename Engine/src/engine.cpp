#include "engine.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ogl_api.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

static DE::GL::shader_program_t * shader;

void DE::clear(DE::Color & color)
{
	DE::GL::clear(color);
}

void DE::clear()
{
	DE::GL::clear();
}

void DE::init_engine()
{
	DE::GL::init_opengl();
	const char *vsource= "#version 330 core\n"
		"layout (location = 0)in vec3 aPos;\n"
		"layout (location = 1)in vec2 aTexCoord;\n"
		"uniform mat4 p_mat = mat4(1.0f);\n"
		"uniform mat4 m_mat = mat4(1.0f);\n"
		"out vec3 col;\n"
		"out vec2 tex_coord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =  p_mat * m_mat * vec4(aPos, 1.0f);\n"
		"	col = aPos;"
		"	tex_coord = aTexCoord;"
		"}\0";

	const char *fsource= "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 col;\n"
		"in vec2 tex_coord;\n"
		"uniform sampler2D tex;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(tex, tex_coord) * vec4(col, 1.0f);\n"
		"}\n\0";
	shader = DE::GL::create_shader(fsource, vsource);
	glUseProgram(shader->shader_id);
	DE::GL::glCheckError_(__FILE__, __LINE__);
}

void DE::set_window_bounds(float xbegin, float ybegin, float xend, float yend)
{
	glm::mat4 proj_mat = glm::ortho(xbegin, xend, yend, ybegin, -4.0f, 100.0f );
	DE::GL::setu_mat4(shader, "p_mat", proj_mat);
}

int DE::create_mesh2d(float *vertices, int vsize)
{
	auto vao = DE::GL::create_vao(vertices, vsize);
	return vao;
}

int DE::create_mesh2d(float *vertices, int vsize, unsigned int * indices, int isize)
{
	auto vao = DE::GL::create_vao(vertices, vsize, indices, isize);
	return vao;
}

int DE::create_mesh(DE::GL::vao_data_t vd)
{
	auto vao = DE::GL::create_vao(&vd);
	return vao;
}

int DE::create_texture(const char * path)
{
	int tex_id = -1;
	int width, height, depth;
	unsigned char * data = stbi_load(path, &width, &height, &depth, 4);
	if(data)
	{
		auto tex_id = DE::GL::create_texture(data, width, height, depth);
		return tex_id;
	}
	return tex_id;
}

void DE::draw_mesh2d(int mesh_id)
{
	glBindVertexArray(mesh_id);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DE::draw_mesh2d(Mesh *mesh)
{
	glm::mat4 m_mat = glm::translate(glm::mat4(1.0f), glm::vec3(mesh->x, mesh->y, 0.0f));
	m_mat = glm::scale(m_mat, glm::vec3(mesh->scale));
	setu_mat4(shader, "m_mat", m_mat);

	DE::GL::draw_mesh(mesh->vao_id, mesh->vertex_count, mesh->texture_id);
}

void DE::destroy_engine()
{
	delete shader;
}

