#version 330 core

layout(location = 0) in vec3 inPosition;

//uniform mat4 uWorld;

void main()
{
	gl_Position = vec4(inPosition, 1.0f);
}