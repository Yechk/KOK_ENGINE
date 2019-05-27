#version 460 core

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

layout (local_size_x = 16,  local_size_y = 16, local_size_z = 1 ) in;

layout (binding=1, rgba16f) readonly uniform image2D original;
layout (binding=2, rgba16f) readonly uniform image2D original2;
layout (binding=3, rgba16f) writeonly uniform image2D result;

void main()
{
  ivec2 currentCoor = ivec2(gl_GlobalInvocationID.xy);

  //additive function

	vec4 color0 = imageLoad(original, currentCoor);
  vec4 color1 = imageLoad(original2, currentCoor);

	float factor0 = 0.5;
  float factor1 = 0.5;

  //imageStore(result, currentCoor, (color0 * factor0) + (color1 * factor1));
  imageStore(result, currentCoor, color0 + color1);
}
