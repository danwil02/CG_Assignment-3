#version 150

in vec3 a_vertex;
in vec4 a_colour;

uniform mat4 camera_matrix;
uniform mat4 projection_matrix;
uniform mat4 scale_matrix;

out vec4 colour;

void main()
{
	colour = a_colour;

	gl_Position = projection_matrix * camera_matrix * (scale_matrix * vec4(a_vertex, 1));

}