#version 330 core

layout (location = 0) in vec3 inPos;

uniform vec3 uColor;

out vec3 color;

void main()
{
	gl_Position = vec4(inPos, 1.0f);
	color = uColor;
}