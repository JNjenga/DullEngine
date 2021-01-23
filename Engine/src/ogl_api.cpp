#include "dull_engine.h"
#include "ogl_api.h"
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp> 
#include <glm/gtc/type_ptr.hpp> 

void DE::GL::init_opengl()
{
}

DE::GL::shader_program_t *
DE::GL::create_shader(const char * fsource, const char * vsource)
{
	unsigned int v_program, f_program, shader_id;
	int success;
	char infoLog[512];

	v_program = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_program, 1, &vsource, NULL);
	glCompileShader(v_program);

	glGetShaderiv(v_program, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(v_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};


	f_program = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_program, 1, &fsource, NULL);
	glCompileShader(f_program);

	glGetShaderiv(f_program, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(f_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	shader_id = glCreateProgram();
	glAttachShader(shader_id, v_program);
	glAttachShader(shader_id, f_program);

	glLinkProgram(shader_id);
	
	auto shader_program = new shader_program_t;
	shader_program->shader_id = shader_id;
	return shader_program;
}

int DE::GL::reload_shader(int shader_id, int shader_type,  const char * vsource)
{
	glDeleteProgram(shader_id);
	// shader_id = DE::GL::create_shader();
	return shader_id;
}

int DE::GL::get_uniform_loc(shader_program_t * shader, const char * name)
{
	auto it = shader->uniforms.find(name);

	if(it != shader->uniforms.end())
		return it->second;

	int index = glGetUniformLocation(shader->shader_id, name);
	if (index == -1)
		shader->uniforms.insert({name, index});
	return index; 
}

int DE::GL::setu_float(const char * name, float value)
{
	return -1;
}

int DE::GL::setu_int(shader_program_t * shader, const char * name, int value)
{
	return -1;
}

int DE::GL::setu_mat4(shader_program_t *shader, const char * name, glm::mat4 value)
{
	glUniformMatrix4fv(DE::GL::get_uniform_loc(shader, name),1, GL_FALSE,glm::value_ptr(value));
	return -1;
}

int DE::GL::create_vao(float *vertices, int vsize)
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vsize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glCheckError_(__FILE__, __LINE__);

	return vao;
}

int DE::GL::create_vao(float *vertices, int vsize, unsigned int * indices, int isize)
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vsize, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
    
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * isize, indices, GL_STATIC_DRAW);

	glCheckError_(__FILE__, __LINE__);

	return vao;
}

int DE::GL::create_vao(vao_data_t * vd)
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vd->vertices) * vd->vsize, vd->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);
	
	glCheckError_(__FILE__, __LINE__);

	if(vd->tsize > 0)
	{
		unsigned int tbo;
		glGenBuffers(1, &tbo);
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vd->texture_coords) * vd->tsize, vd->texture_coords, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0));
		glEnableVertexAttribArray(1);
		glCheckError_(__FILE__, __LINE__);
	}
	
	if(vd->isize > 0)
	{
		unsigned int ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vd->indices) * vd->isize, vd->indices, GL_STATIC_DRAW);
		glCheckError_(__FILE__, __LINE__);
	}

	return vao;
}

int DE::GL::create_texture(unsigned char * data, int width, int height, int depth  )
{
	unsigned int tex_id;
	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if(depth == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	return tex_id;
}


void DE::GL::draw_mesh(int vao, int vertex_count, int tex_id)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_id);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);

	glCheckError_(__FILE__, __LINE__);
}

/*
void DE::GL::draw_mesh(int vao, int mode, int vertex_count)
{
    glBindVertexArray(vao);
    glDrawElements(mode, vertex_count, GL_UNSIGNED_INT, 0);
}

void DE::GL::draw_mesh(int vao, int mode, int vertex_count, int tex_id)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_id);
    glBindVertexArray(vao);
    glDrawElements(mode, vertex_count, GL_UNSIGNED_INT, 0);
}
*/

int DE::GL::glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
			case GL_INVALID_ENUM:
				error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:
				error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:
									   error = "STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW:
									   error = "STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY:
									   error = "OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
									   error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}

		printf("%s | %s (%d) \n", error.c_str(), file, line);
	}
	return errorCode;
}
