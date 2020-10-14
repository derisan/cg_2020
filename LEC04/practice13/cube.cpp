#include "cube.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Cube::Cube()
	: mState{ State::kActive },
	mPosition{ -1.0f, sin(glm::radians(static_cast<float>(-200))), 0.0f },
	mScale{ 0.05f, 0.1f, 0.1f },
	mRotation{ 0.0f },
	mRecomputeWorldTransform{ true },
	mVertexArray{ nullptr },
	mAngle{ 0.0f },
	mSinNum{ -200 },
	mShouldTravel{ false },
	mShouldRotate{ false },
	mShouldScale{ false },
	mPath{ &Cube::SinTravel }

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
		if (mShouldRotate)
			Rotate(dt);

		if (mShouldTravel)
			(this->*mPath)(dt);

		if (mShouldScale)
			Scale(dt);

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

void Cube::SinTravel(float dt)
{
	++mSinNum;
	if (mSinNum > 200)
		mSinNum = -200;
	mPosition.x = 0.005f * mSinNum;
	mPosition.y = sin(glm::radians(static_cast<float>(mSinNum)));
}

void Cube::Rotate(float dt)
{
	mRotation += cos(dt);
}

void Cube::Scale(float dt)
{
	mAngle += dt;

	mScale.x += cos(mAngle) * 0.005f;
	mScale.y += cos(mAngle) * 0.005f;
	mScale.z += cos(mAngle) * 0.005f;
}

void Cube::Reset()
{
	mShouldTravel = false;
	mShouldRotate = false;
	mShouldScale = false;

	//mPosition = glm::vec3{ -1.0f, sin(glm::radians(static_cast<float>(-200))), 0.0f };
	mPosition = glm::vec3{ 0.0f, 0.0f, 0.0f };
	mScale = glm::vec3{ 0.05f, 0.1f, 0.1f };
	mRotation = 0.0f;
	mAngle = 0.0f;
	mSinNum = -200;
}

void Cube::SetPath(int value)
{
	switch (value)
	{
	case 1:
		mPath = &Cube::SinTravel;
		break;
	case 2:
		mPath = &Cube::SpringTravel;
		break;
	case 3:
		mPath = &Cube::ZigzagTravel;
		break;
	}
}

void Cube::SpringTravel(float dt)
{
	float r{ 0.5f };
	float a{ -0.7f };
	for (int i = 0; i < 1440; i += 10, a += 0.01f)
		glVertex3f(a + r * cos(glm::radians(float(i))), r * sin(glm::radians(float(i))), 0.0f);
}

void Cube::ZigzagTravel(float dt)
{

}