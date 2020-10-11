#include "pyramid.h"

#include "shader.h"
#include "vertexarray.h"

Pyramid::Pyramid()
	: mVertexArray{ nullptr },
	mAngle{ 0.0f }
{
	Load();
}

Pyramid::~Pyramid()
{
	delete mVertexArray;
}

void Pyramid::Load()
{
	const float vertices[] = {
		// pos				// color
		-0.5, 0,  0.5,		1.0, 0.0, 0.0,
		-0.5, 0,  -0.5,		0.0, 1.0, 0.0,
		 0.5, 0,  0.5,		0.0, 0.0, 1.0,
		 0.5, 0,  -0.5,		1.0, 1.0, 0.0,
		  0,  0.5,  0,		0.0, 1.0, 1.0,
	};

	const unsigned int indices[] = {
		0, 4, 1,
		0, 2, 4,
		4, 2, 3,
		4, 3, 1,
		0, 1, 2,
		2, 1, 3
	};

	mVertexArray = new VertexArray(vertices, 5, indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
}

void Pyramid::Update(float dt)
{
	Object::Update(dt);

	if (GetState() == State::kActive)
	{
		mAngle += cos(dt);
		SetRotation(mAngle);
	}
}

void Pyramid::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}
