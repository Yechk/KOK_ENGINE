#version 460 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 aTexCoord;
layout(location = 1) in vec3 vertexPosition;
layout(location = 2) in vec4 xyzs; //particle center and size
layout(location = 3) in float alpha; //transparency

// Values that stay constant for the whole mesh.
uniform vec3 cameraRight;
uniform vec3 cameraUp;
uniform mat4 VP;


out vec2 TexCoord;
out float opacity;

void main()
{
	float size = xyzs.w;
	vec3 particleCenter = xyzs.xyz;

	vec3 vertexPositionWorld =
		particleCenter
		+ cameraRight * vertexPosition.x * size
		+ cameraUp * vertexPosition.z * size;

	opacity = alpha;

	gl_Position =  VP * vec4(vertexPositionWorld,1.0);
	TexCoord = aTexCoord;
}
