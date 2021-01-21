#version 330 core

out vec4 frag_color;
in vec3 col;
in vec2 tex_coord;

uniform sampler2D tex;

void main()
{
	frag_color = texture(tex, tex_coord) * vec4(col, 0.5f);
}