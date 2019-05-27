//text frag shader
#version 460 core
out vec4 color;

uniform sampler2D imaget;
uniform vec4 colorMod;

in vec2 TexCoord;

void main()
{
	color = texture(imaget, TexCoord) * colorMod;
}
