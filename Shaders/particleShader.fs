#version 460 core

layout(location = 0) out vec4 color;

in vec2 TexCoord;
uniform sampler2D diffuseTex;

in float opacity;

void main()
{


	color = texture(diffuseTex, TexCoord).rgba * vec4(1.0f, 1.0f, 1.0f, opacity);
	//color = vec4(1.0f);



}
