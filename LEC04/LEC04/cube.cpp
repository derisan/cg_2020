#include "cube.h"

#include "shader.h"
#include "vertexarray.h"

Cube::Cube()
	: mVertexArray{ nullptr },
	mAngle{ 0.0f }
{
	Load();
}

Cube::~Cube()
{
	delete mVertexArray;
}

void Cube::Load()
{
	const float vertices[] = {
		// pos				// color
		-0.5, -0.5,  0.5,	1.0, 0.0, 0.0,
		 0.5, -0.5,  0.5,	0.0, 1.0, 0.0,
		 0.5,  0.5,  0.5,	0.0, 0.0, 1.0,
		-0.5,  0.5,  0.5,	0.5, 0.5, 0.5,
		-0.5, -0.5, -0.5,	0.5, 0.0, 0.0,
		 0.5, -0.5, -0.5,	0.0, 0.5, 0.0,
		 0.5,  0.5, -0.5,	0.0, 0.0, 0.5,
		-0.5,  0.5, -0.5,	0.5, 0.5, 0.5
	};

	const unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3
	};

	mVertexArray = new VertexArray(vertices, 8, indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
}

void Cube::Update(float dt)
{
	Object::Update(dt);

	if (GetState() == State::kActive)
	{
		mAngle += cos(dt);
		SetRotation(mAngle);
	}
}

void Cube::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

