#version 150

in vec3 a_vertex;
in vec3 a_normal;

uniform mat4 camera_matrix;
uniform mat4 projection_matrix;
uniform mat4 scale_matrix;
uniform mat3 normal_matrix;

out vec3 normal;
out vec4 vertex;

void main()
{
	normal = normalize(normal_matrix * a_normal);
	vertex = camera_matrix * (scale_matrix * vec4(a_vertex, 1));

	gl_Position = projection_matrix * vertex;
}