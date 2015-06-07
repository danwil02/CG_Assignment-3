#version 150

in vec3 a_vertex;
in vec2 a_texCoords;

uniform mat4 camera_matrix;
uniform mat4 projection_matrix;

out vec2 st;

void main()
{
	vec4 vertex = camera_matrix * vec4(a_vertex, 1);

	gl_Position = projection_matrix * vertex;
	st = a_texCoords;
}