#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uOut;

void main()
{
	gl_Position = uProj * uView * uOut * uWorld * vec4(inPos, 1.0f);
}