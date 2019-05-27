#version 460 core

#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

layout (local_size_x = 16,  local_size_y = 16, local_size_z = 1 ) in;


layout (binding=0, RGBA8) readonly uniform image2D original;
layout (binding=1, RGBA8) writeonly uniform image2D result;

void main()
{
  ivec2 currentCoor = ivec2(gl_GlobalInvocationID.xy);

  vec4 color = vec4(imageLoad(original, currentCoor).rgb, 1.0);

  imageStore(result, currentCoor, color);
}
