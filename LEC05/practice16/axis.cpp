#include "axis.h"

#include <gl/glew.h>

#include "shader.h"
#include "vertexarray.h"

Axis::Axis()
	: mVertexArray{ nullptr }
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
	const float vertices[] = {
		// pos				// color
		-2.0,  0.0,  0.0,	1.0, 0.0, 0.0,
		 2.0,  0.0,  0.0,	1.0, 0.0, 0.0,
		 0.0,  2.0,  0.0,	0.0, 1.0, 0.0,
		 0.0, -2.0,  0.0,	0.0, 1.0, 0.0,
		 0.0, 0.0,   2.0,	0.0, 0.0, 1.0,
		 0.0, 0.0,  -2.0,	0.0, 0.0, 1.0
	};

	mVertexArray = new VertexArray(vertices, 6);
}