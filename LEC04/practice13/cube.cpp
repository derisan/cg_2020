#include "cube.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Cube::Cube()
	: mState{ State::kActive },
	mPosition{ 0.0f, 0.0f, 0.0f },
	mScale{ 0.05f, 0.1f, 0.1f },
	mRotation{ 0.0f },
	mRecomputeWorldTransform{ true },
	mVertexArray{ nullptr },
	mNum{ -200 }
{
	Load();
}

Cube::~Cube()
{
	delete mVertexArray;
}

void Cube::Update(float dt)
{
	if (mRecomputeWorldTransform)
		ComputeWorldTransform();

	if (mState == State::kActive)
	{
		mRotation += cos(dt);

		++mNum;
		
		if (mNum > 200)
			mNum = -200;

		mPosition.x = 0.005f * mNum;
		mPosition.y = sin(glm::radians(static_cast<float>(mNum)));

		mRecomputeWorldTransform = true;
	}
}

void Cube::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrixUniform("uWorld", mWorldTransform);
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Cube::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mWorldTransform = glm::mat4{ 1.0f };
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
		mWorldTransform = glm::translate(mWorldTransform, mPosition);
		mWorldTransform = glm::scale(mWorldTransform, mScale);
	}
}

void Cube::Load()
{
	const float vertices[] = {
		// pos				// color
		-0.5, -0.5,  0.5,	
		 0.5, -0.5,  0.5,	
		 0.5,  0.5,  0.5,	
		-0.5,  0.5,  0.5,	
		-0.5, -0.5, -0.5,	
		 0.5, -0.5, -0.5,	
		 0.5,  0.5, -0.5,	
		-0.5,  0.5, -0.5
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