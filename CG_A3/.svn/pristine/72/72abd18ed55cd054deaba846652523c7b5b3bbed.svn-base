#version 150

in vec3 a_vertex;
in vec2 a_tex_coord;
in vec3 a_normal;

uniform mat4 camera_matrix;
uniform mat4 projection_matrix;
uniform mat4 modleview_matrix;
uniform mat3 normal_matrix;

out vec2 st;
out vec3 normal;
out vec4 vertex;

void main()
{
	st = a_tex_coord;
	normal = normalize(normal_matrix * a_normal);
	vertex = camera_matrix * (modleview_matrix * vec4(a_vertex, 1));

	gl_Position = projection_matrix * vertex;
}