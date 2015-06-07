#version 150

in vec2 st;
in vec3 normal;
in vec4 vertex;
in vec4 ShadowCoord;

out vec4 fragColour;
out float fragmentdepth;

uniform sampler2D gShadowMap;
uniform int shadow;

uniform sampler2D texMap;

uniform vec4 light_pos;

uniform int apply_tex;

uniform vec3 light_ambient;     // Light ambient RGBA values
uniform vec3 light_diffuse;     // Light diffuse RGBA values  
uniform vec3 light_specular;    // Light specular RGBA values

uniform vec3 mtl_ambient;  // Ambient surface colour
uniform vec3 mtl_diffuse;  // Diffuse surface colour
uniform vec3 mtl_specular; // Specular surface colour

uniform float shininess; //const float shininess = 32;

uniform vec3 emission;
uniform float alpha;
// This is the same function that appeared in the vertex shader for
// per-vertex lighting. Now it is being calculated for each fragment
// individually.
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

/*
	if(light_ambient == vec3(0,0,0) && light_diffuse == vec3(0,0,0) && light_specular == vec3(0,0,0))
	{
		return vec3(0.5,0.5,0.5);
	}
	*/
    return ambient + diffuse + spec;
}

vec3 expFog(in vec3 rgb, in float distance, in float b)
{
	vec3 fogColour = vec3(0.5,0.6,0.7);
	float fogAmount = 1.0 - exp(-distance * b);
	return mix(rgb,fogColour,fogAmount);
}

void main(void) 
{
	if(shadow == 0)
	{
		// Fog

		float fFogCoord = abs(vertex.z)/10;

		vec4 texColour = texture(texMap, st);
		vec3 phLight = vec3(phongPointLight(vertex, normalize(normal)));
		vec4 phongLight = vec4(expFog(phLight,fFogCoord, 0.005), 1.0);
		vec4 colour;

		if(apply_tex == 0)
		{
			colour = phongLight;
		}
		else
		{
			colour = phongLight * texColour;
		}
		
		float bias = 0.004;
        float visibility = 1.0;
        if ( texture( gShadowMap, ShadowCoord.xy ).x  <  ShadowCoord.z-bias){
            visibility = 0.5;
        }
        

		vec4 gamma = vec4(vec3(1.0/2.2),1.0);
		fragColour = visibility * pow(colour + vec4(emission,1.0),gamma);
		fragColour.a = alpha;
		
		
	}
	else if(shadow == 3) // No shadow (workaround for lambo for the moment)
	{
		// Fog

		float fFogCoord = abs(vertex.z)/10;

		vec4 texColour = texture(texMap, st);
		vec3 phLight = vec3(phongPointLight(vertex, normalize(normal)));
		vec4 phongLight = vec4(expFog(phLight,fFogCoord, 0.005), 1.0);
		vec4 colour;

		if(apply_tex == 0)
		{
			colour = phongLight;
		}
		else
		{
			colour = phongLight * texColour;
		}
		
		vec4 gamma = vec4(vec3(1.0/2.2),1.0);
		fragColour = pow(colour + vec4(emission,1.0),gamma);
		fragColour.a = alpha;
	}
	else
	{
        fragmentdepth = gl_FragCoord.z;
	}

	//fragColour = vec4(.5,.5,.5,1);
    //fragColour = texture(texMap, st);
}