#version 460 core

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

struct VertexBoneData
{
  uint boneID[4];
  float weights[4];
};

struct Vertex
{
	vec3 transPosition;
	vec3 position;
	vec3 normal;
	vec2 texCoords;
	vec3 tangent;
};

layout (local_size_x = 1,  local_size_y = 1, local_size_z = 1 ) in;

layout (std140, binding = 1) buffer vertexData
{
  Vertex vertices[];
};

layout (std140, binding = 2) buffer BUB
{
  mat4 boneTransforms[];
};

layout (std430, binding = 3) buffer VBD
{
  VertexBoneData boneDatas[];
};

void main()
{
  uint i = gl_GlobalInvocationID.x;
  mat4 boneTrans = boneTransforms[boneDatas[i].boneID[0]] * boneDatas[i].weights[0];
  boneTrans += boneTransforms[boneDatas[i].boneID[1]] * boneDatas[i].weights[1];
  boneTrans += boneTransforms[boneDatas[i].boneID[2]] * boneDatas[i].weights[2];
  boneTrans += boneTransforms[boneDatas[i].boneID[3]] * boneDatas[i].weights[3];

  vec4 tr = boneTrans * vec4(vertices[i].position, 1.0f);
  vertices[i].transPosition = vec3(tr.x, tr.y, tr.z);
}
