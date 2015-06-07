#version 150

in vec3 a_vertex;

uniform mat4 camera_matrix;
uniform mat4 projection_matrix;
uniform mat4 scale_matrix;

out vec4 colour;

void main()
{
	colour = vec4(0.0f,0.0f,0.0f,1.0f);

	gl_Position = projection_matrix * camera_matrix * (scale_matrix * vec4(a_vertex, 1));
}