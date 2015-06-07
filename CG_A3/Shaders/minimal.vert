#version 150

in vec3 a_vertex;
//in vec4 a_colour;

out vec4 colour;

void main(){

	//colour = a_colour;
	colour = vec4(.1,.2,.4,1);
	gl_Position = vec4(a_vertex, 1);
}