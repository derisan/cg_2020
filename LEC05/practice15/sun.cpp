#include "sun.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Sun::Sun()
	: mWorldTransform{ 1.0f },
	mPosition{ 0.0f },
	mScale{ 1.0f },
	mRotation{ 0.0f },
	mRecomputeWorldTransform{ true },
	mVertexArray{ nullptr }
{
	Load();
}

void Sun::Update(float dt)
{
	if (mRecomputeWorldTransform)
		ComputeWorldTransform();

	mRotation += cos(dt);
	SetRotation(mRotation);
}

void Sun::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorld", mWorldTransform);
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Sun::ComputeWorldTransform()
{
	mRecomputeWorldTransform = false;

	mWorldTransform = glm::mat4{ 1.0f };
	mWorldTransform = glm::translate(mWorldTransform, mPosition);
	mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
	mWorldTransform = glm::scale(mWorldTransform, glm::vec3{ mScale });
}

void Sun::Load()
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