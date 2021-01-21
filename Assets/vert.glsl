#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 p_mat;
uniform mat4 m_mat;

out vec3 col;
out vec2 tex_coord;

void main()
{
	gl_Position = p_mat * m_mat * vec4(aPos, 1.0f);
	col = aPos;
	tex_coord = aTexCoord;
}