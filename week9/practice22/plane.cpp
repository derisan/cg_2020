#include "plane.h"

#include <GL/glew.h>

#include "vertexarray.h"

Plane::Plane()
	: Object{},
	mVertexArray{ nullptr }
{
	Load();
}

Plane::~Plane()
{
	delete mVertexArray;
}

void Plane::Update()
{
	if (GetState() == State::kActive)
		Object::Update();
}

void Plane::Draw(Shader* shader)
{
	Object::Draw(shader);

	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Plane::Load()
{
	const float vertices[] = {
		 -0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,
	};

	const unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2
	};

	mVertexArray = new VertexArray{ vertices, static_cast<unsigned int>(sizeof(vertices) / sizeof(float)), indices, 
		sizeof(indices) / sizeof(unsigned int)};
}