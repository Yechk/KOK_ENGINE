//this shader contains post process and deferred lighting techniques for the ENGINE
//
//draws on a full screen quad.
#version 460 core

out vec4 color;

in vec2 TexCoords;

//input textures from gBuffer
uniform sampler2D tex_ssao;
uniform sampler2D tex_lighting;
uniform sampler2D tex_depth;

//bloom input for first half
uniform sampler2D tex_bloomH;

vec3 ReinHard(float exposure, vec3 hdrColor)
{
	// reinhard tone mapping
	vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
	// gamma correction
	return mapped;//pow(mapped, vec3(1.0 / 2.2));

}

//simple blur function
vec3 Blur(sampler2D tex, int kernelSize)
{
	vec2 texelSize = 1.0 / vec2(textureSize(tex, 0));
	vec3 result = vec3(0.0);

	for (int x = -kernelSize/2; x < kernelSize/2; x++)
	{
		for(int y = -kernelSize/2; y < kernelSize/2; y++)
		{
			vec2 offset = vec2(float(x), float(y)) * texelSize;
			result += texture(tex, TexCoords + offset).rgb;
		}
	}

	return result / (kernelSize * kernelSize);
}

vec3 Gamma(vec3 scrColor)
{
	return pow(scrColor, vec3(1.0 / 2.2));

}

vec3 blurV()
{
	float weight[10] = float[] (0.197413, 0.174667, 0.120978, 0.065591, 0.027835, 0.009245, 0.002403, 0.000489, 0.000078, 0.00001); //TODO: definitely bake into a texture

	vec2 texelSize = 2.0 / vec2(textureSize(tex_bloomH, 0));

  //blur function
  vec3 rt = texture(tex_bloomH, TexCoords).rgb * weight[0];

	for (int x = 1; x < 10; x++)
	{
		rt += texture(tex_bloomH, TexCoords + (texelSize * vec2(0.0, x))).rgb * weight[x];
    rt += texture(tex_bloomH, TexCoords - (texelSize * vec2(0.0, x))).rgb * weight[x];
	}

	return rt;
}

void main()
{
  //load all texture info for fragment
  //vec3 ssao = texture(tex_ssao, TexCoords).rgb;
	vec4 lighting = vec4(blurV() * 2.0f, 0.0f) + texture(tex_lighting, TexCoords);

	vec3 ambient = Blur(tex_ssao, 4) * vec3(lighting.a) * 0.1f;


  color = vec4(ReinHard(1.8, lighting.rgb + ambient), 1.0f);
	//color = vec4(Blur(tex_ssao, 4), 1.0f);
	gl_FragDepth = 1.0 - texture(tex_depth, TexCoords).r;
}
