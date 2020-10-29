#version 330 core

layout (location = 0) in vec3 inPos;

uniform mat4 uWorld;
uniform vec3 uColor;

out vec3 color;

void main()
{
	gl_Position = uWorld * vec4(inPos, 1.0f);
	color = uColor;
}