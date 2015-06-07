#version 150
//
//
//  WATER FRAGMENT SHADER
//
//

in vec3 normal;
in vec4 vertex;
in vec2 st;
in vec4 ShadowCoord;

out vec4 fragColour;

uniform sampler2D gShadowMap;
uniform sampler2D nMap;
uniform sampler2D animMap;
uniform sampler2D reflectionTex;

uniform vec4 light_pos;

uniform vec3 light_ambient;     // Light ambient RGBA values
uniform vec3 light_diffuse;     // Light diffuse RGBA values  
uniform vec3 light_specular;    // Light specular RGBA values

uniform vec3 mtl_ambient;  // Ambient surface colour
uniform vec3 mtl_diffuse;  // Diffuse surface colour
uniform vec3 mtl_specular; // Specular surface colour

uniform float shininess; //const float shininess = 32;

uniform vec3 emission;
uniform float alpha;

vec3 phongPointLight(in vec4 position, in vec3 norm)
{
    vec3 s = normalize(vec3(light_pos - position));
    vec3 v = normalize(-position.xyz);
    vec3 r = reflect( -s, norm );
    
    vec3 ambient = light_ambient * mtl_ambient;
	
    // The diffuse component
    float sDotN = max( dot(s,norm), 0.0 );
    vec3 diffuse = light_diffuse * mtl_diffuse * sDotN;

    // The specular component
    vec3 spec = vec3(0.0);
    if ( sDotN > 0.0 )
		spec = light_specular * mtl_specular *
            pow( max( dot(r,v), 0.0 ), shininess );

    return ambient + diffuse + spec;
}

void main(void) 
{
	// Fog
	vec3 NN = texture(nMap,st).xyz;
	vec3 N = normal + normalize(2.0*NN.xyz-1.0);

	vec3 NN_animation = texture(animMap,st).xyz;
	vec3 N_animation = normal + normalize(2.0*NN_animation.xyz-1.0);

	N = mix(N,N_animation,0.5);

	float fFogCoord = abs(vertex.z)/10;

	vec4 phongLight = vec4(phongPointLight(vertex, normalize(N)),1);
	
	float bias = 0.004;
    float visibility = 1.0;
    if ( texture( gShadowMap, ShadowCoord.xy ).x  <  ShadowCoord.z-bias){
        visibility = 1.0;
    }

	vec4 gamma = vec4(vec3(1.0/2.2),1.0);
	vec4 gammaCorrectedColour = visibility * pow(phongLight + vec4(emission,1.0),gamma);

	// Reflections
	vec2 reflectCoords = vertex.xy;
	// Vertices x, y coords are between -1000 and 1000
	reflectCoords.x += 1000;
	reflectCoords.y += 1000;
	reflectCoords.x /= 2000;
	reflectCoords.y /= 2000;

	vec4 reflect = texture(reflectionTex, reflectCoords);

	fragColour = (gammaCorrectedColour * visibility);
	fragColour.a = alpha;
	fragColour = mix(fragColour, reflect, 0.5);

}