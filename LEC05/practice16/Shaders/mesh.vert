#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

uniform mat4 uWorld;
uniform mat4 uOut;
uniform mat4 uView;
uniform mat4 uProj;

out vec3 color;

void main()
{
	gl_Position = uProj * uView * uOut * uWorld * vec4(inPosition, 1.0f);

	color = inColor;
}