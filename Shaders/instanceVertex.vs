#version 460 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 NM;
out vec4 n;

void main()
{	
	n = normalize(NM * vec4(normal,0.0));
	gl_Position =  MVP * vec4(vertexPosition_modelspace + vec3(0,0,gl_InstanceID*2.3f),1);
}

