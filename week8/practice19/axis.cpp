#include "axis.h"

#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Axis::Axis(Color color)
	: Object{ color },
	mVertexArray{ nullptr }
{
	Load();
}

Axis::~Axis()
{
	delete mVertexArray;
}

void Axis::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawArrays(GL_LINES, 0, 6);
}

void Axis::Load()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-2.0,  0.0,  0.0,	color.x, color.y, color.z,
		 2.0,  0.0,  0.0,	color.x, color.y, color.z,
		 0.0,  2.0,  0.0,	color.x, color.y, color.z,
		 0.0, -2.0,  0.0,	color.x, color.y, color.z,
		 0.0, 0.0,   2.0,	color.x, color.y, color.z,
		 0.0, 0.0,  -2.0,	color.x, color.y, color.z
	};

	mVertexArray = new VertexArray(vertices, 6);
}