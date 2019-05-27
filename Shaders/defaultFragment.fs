#version 460 core

layout(location = 0) out vec4 color;

uniform float ambient;
uniform float hardness;
uniform int emissive; 

uniform vec3 surface;

in vec2 TexCoord;
uniform sampler2D diffuseTex;

in vec4 n;

void main()
{	
	float w = 0.5;
	vec3 cl = texture(diffuseTex, TexCoord).rgb;
	vec3 nm = normalize(-n.xyz);
	vec3 diffuseColor = vec3(1.0f,0.95f,0.88f);
	vec3 diffuse = diffuseColor * max(clamp((dot(nm, vec3(0.5,-0.5,0.0)) + w) / ((1 + w)*(1 + w)),0.0,1.0), 0.0);


	color = vec4((cl * diffuse)+ambient,1.0);
}	
