//text vertex shader
#version 460 core

layout (location = 0) in vec2 vertex;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 projection;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * vec4(vertex.x, vertex.y, 0.0, 1.0);
//	TexCoord = vec2(0.5,-0.5) * (gl_Position.xy + 1.0);
	TexCoord = aTexCoord;
}
