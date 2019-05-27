//text frag shader
#version 460 core
out vec4 color;

uniform vec3 textColor;

uniform vec2 origin;
uniform vec2 dims;

in vec2 TexCoord;

//uniform bool line;

void main()
{
	bool line = false;
	//float outline = 3.0f;

	//if (gl_FragCoord.x > origin.x - dims.x + outline && gl_FragCoord.x < origin.x - outline && gl_FragCoord.y > origin.y + outline &&
	//	gl_FragCoord.y < origin.y + dims.y - outline)
	//{
	//	line = false;
	//}

	if (line == false)
		color = vec4(textColor, 1.0f);
	else
		color = vec4(textColor*0.5,1.0);
}
