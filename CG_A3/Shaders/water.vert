#version 150
//
//
//  WATER VERTEX SHADER
//
//

in vec3 a_vertex;
in vec2 a_tex_coord;

uniform float a_time;
uniform mat4 camera_matrix;
uniform mat4 projection_matrix;
uniform mat4 modleview_matrix;
uniform mat3 normal_matrix;

uniform mat4 DepthBiasMVP;

out vec3 normal;
out vec4 vertex;
out vec4 ShadowCoord;
out vec2 st;

void main()
{
	vec3 vert = a_vertex;
	vert.y = 3*(1+sin(.001 * a_time + 5*a_vertex.x + cos(5*a_vertex.z)))/2;


	vec3 loc_normal = vec3(0,1,0);
	normal = normalize(normal_matrix * loc_normal);
	vertex = camera_matrix * (modleview_matrix * vec4(vert, 1));

	gl_Position = projection_matrix * vertex; 
	st = a_tex_coord;
    ShadowCoord = DepthBiasMVP * vec4(vert,1.0);
}