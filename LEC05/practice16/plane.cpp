#include "plane.h"

#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Plane::Plane()
	: mVertexArray{ nullptr }
{
	Load();
}

Plane::~Plane()
{
	delete mVertexArray;
}

void Plane::Load()
{
	const float vertices[] = {
		// pos				// color
		-0.5, 0.0,  0.0,	1.0, 0.0, 0.0,
		 0.5, 0.0,  0.0,	0.0, 1.0, 0.0,
		 0.5, 0.0,  1.0,	0.0, 0.0, 1.0,
		-0.5, 0.0,  1.0,	0.0, 0.5, 0.5,
	};

	const unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	mVertexArray = new VertexArray(vertices, 4, indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
}

void Plane::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}