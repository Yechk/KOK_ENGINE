#version 460 core

layout(location = 0) in vec3 in_position;

void main()
{	
	gl_Position =  in_position;
}
