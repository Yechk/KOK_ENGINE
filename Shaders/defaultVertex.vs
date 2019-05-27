#version 460 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 aTexCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 NM;
uniform mat4 M;
out vec4 n;
out vec2 TexCoord;

void main()
{	
	n = normalize(NM * vec4(normal,0.0));
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	TexCoord = aTexCoord;
}

