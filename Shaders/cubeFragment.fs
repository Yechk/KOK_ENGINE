#version 460 core

layout(location = 0) out vec4 color;

in vec3 TexCoord;
uniform samplerCube diffuseTex;

void main()
{
	color = texture(diffuseTex, TexCoord);
	//color = vec4(1.0f);
}
