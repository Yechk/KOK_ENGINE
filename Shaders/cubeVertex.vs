#version 460 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
out vec3 TexCoord;

void main()
{
	vec4 pos =  MVP * vec4(vertexPosition_modelspace,1.0);
	TexCoord = vertexPosition_modelspace;
	gl_Position = pos.xyww;
}
