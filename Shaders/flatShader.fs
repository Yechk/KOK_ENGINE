#version 460 core

layout(location = 0) out vec4 position;
layout(location = 1) out vec4 normals;
layout(location = 2) out vec4 diffuse;
layout(location = 3) out vec4 directional;
layout(location = 4) out vec4 ssPosition;
layout(location = 5) out vec4 ssNormal;


//uniform float ambient;
uniform float hardness;
uniform int emissive;

uniform vec3 surface;

in vec2 TexCoord;
uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D OSHTex;

in vec3 rNormal;
in vec3 rWorldPos;

in vec3 ssaoNormal;
in vec3 ssaoPosition;

void main()
{
	vec3 dTexture = texture(diffuseTex, TexCoord  * 1.0f).rgb;

	diffuse = vec4(dTexture, gl_FragCoord.z);
	normals = vec4(normalize(rNormal), 1.0);
	position = vec4(rWorldPos, 1.0);

	ssNormal = vec4(normalize(ssaoNormal), 1.0);
	ssPosition = vec4(ssaoPosition, 1.0);

	directional = vec4(1,0,1,0);


}
