#version 460 core

layout(location = 0) out vec4 position;
layout(location = 1) out vec4 normals;
layout(location = 2) out vec4 diffuse;
layout(location = 3) out vec4 emissiveAmbient;
layout(location = 4) out vec4 ssPosition;
layout(location = 5) out vec4 ssNormal;
layout(location = 6) out float depth;
layout(location = 7) out vec4 specularGloss;


uniform bool useMaps;

in vec2 TexCoord;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D emissiveAmbientTex;
uniform sampler2D specularGlossTex;

uniform float texScale;

in vec3 rWorldPos;

in vec3 ssaoNormal;
in vec3 ssaoPosition;

in mat3 nTBN;

void main()
{
	//load color and parameter textures
	vec3 dTexture = texture(diffuseTex, TexCoord*texScale).rgb;
	vec4 emissiveAmbientColor = texture(emissiveAmbientTex, TexCoord*texScale);
	vec4 specularGlossColor = texture(specularGlossTex, TexCoord*texScale);

	//save values to output
	emissiveAmbient = emissiveAmbientColor;
	specularGloss = specularGlossColor;

	//calculate other values and save
	diffuse = vec4(dTexture, 1.0f);
	depth = gl_FragCoord.z;
	normals = vec4(normalize((nTBN * (texture(normalTex, TexCoord*texScale).rgb * 2.0 - 1.0))), 1.0);
	position = vec4(rWorldPos, 1.0);

	ssNormal = vec4(normalize(ssaoNormal), 1.0);
	ssPosition = vec4(ssaoPosition, 1.0);





}
