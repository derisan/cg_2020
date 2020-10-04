#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;

uniform mat4 world;

out vec3 color;

void main()
{
	gl_Position = world * vec4(inPos, 1.0f);
	color = inColor;
}