#version 460 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 tangent;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec2 TexCoord;

out vec3 rWorldPos;
out mat3 nTBN;
out vec3 ssaoNormal;
out vec3 ssaoPosition;

void main()
{
	mat3 rNMatrix = mat3(M);
	vec3 T = normalize(tangent);
	vec3 N = normalize(normal);
	T = normalize(T - dot(T, N) * N);
	vec3 B = cross(N, T);

	mat3 TBN = rNMatrix * mat3(T, B, N);

	nTBN = TBN;

	ssaoNormal = inverse(rNMatrix) * normal;
	ssaoPosition = vec4(MV * vec4(vertexPosition_modelspace, 1.0)).xyz;
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1.0);
	TexCoord = aTexCoord;

	rWorldPos = vec4(M * vec4(vertexPosition_modelspace,1.0)).xyz;
}
