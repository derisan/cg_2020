#include "frontplane.h"

#include "vertexarray.h"

FrontPlane::FrontPlane(Color color)
	: Plane{ color }
{
	Load();
}

void FrontPlane::Load()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.5, 1.0, 0.0,	    color.x, color.y, color.z,
		-0.5, -0.0, 0.0,	color.x, color.y, color.z,
		 0.5, -0.0, 0.0,	color.x, color.y, color.z,
		 0.5, 1.0, 0.0,	    color.x, color.y, color.z
	};

	const unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	auto vertexArray = new VertexArray(vertices, 4,
		indices, 6);

	SetVertexArray(vertexArray);
}