#version 460 core

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

layout (local_size_x = 16,  local_size_y = 16, local_size_z = 1 ) in;

layout (binding=0, rgba16f) readonly uniform image2D original;
layout (binding=1, rgba16f) writeonly uniform image2D result;

void main()
{
  ivec2 currentCoor = ivec2(gl_GlobalInvocationID.xy);

  //blur function
  int size = 16;
  vec4 rt = vec4(0.0);

	for (int x = -size/2; x < size/2; x++)
	{
		for(int y = -size/2; y < size/2; y++)
		{
			ivec2 offset = ivec2(x, y);
			rt += imageLoad(original, currentCoor + offset);
		}
	}

	vec4 color = rt / (size * size);

  imageStore(result, currentCoor, color);
}
