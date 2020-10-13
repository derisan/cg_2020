#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

out vec3 color;

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
	gl_Position = uProj * uView * uWorld * vec4(inPosition, 1.0f);

	color = inColor;
}