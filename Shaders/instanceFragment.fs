#version 460 core

layout(location = 0) out vec4 color;

uniform float ambient;
uniform float hardness;
uniform int emissive; 

uniform vec3 surface;

in vec4 n;

void main()
{	
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}	
