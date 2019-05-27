#version 460 core

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

layout (local_size_x = 16,  local_size_y = 16, local_size_z = 1 ) in;

layout (binding=3, rgba8) readonly uniform image2D original;
layout (binding=5, rgba8) writeonly uniform image2D result;

float weight[6] = float[] (0.382925, 0.24173, 0.060598, 0.005977, 0.000229, 0.000003);

void main()
{
  ivec2 currentCoor = ivec2(gl_GlobalInvocationID.xy);

  //blur function
  vec4 rt = imageLoad(original, currentCoor) * weight[0];

	for (int x = 1; x < 6; x++)
	{
		rt += imageLoad(original, currentCoor + ivec2(0, x)) * weight[x];
    rt += imageLoad(original, currentCoor - ivec2(0, x)) * weight[x];
	}

  imageStore(result, currentCoor, rt);
}
