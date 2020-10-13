#version 330 core

layout (location = 0) in vec3 iPos;

uniform mat4 uWorld;

void main()
{
	gl_Position = uWorld * vec4(iPos, 1.0f);
}