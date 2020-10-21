#include "plane.h"

#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Plane::Plane(Color color)
	: Object{},
	mVertexArray{ nullptr },
	mColor{ 0.0f }
{
	switch (color)
	{
		case kRed:
			mColor = glm::vec3{ 1.0f, 0.0f, 0.0f };
			break;
		case kGreen:
			mColor = glm::vec3{ 0.0f, 1.0f, 0.0f };
			break;
		case kBlue:
			mColor = glm::vec3{ 0.0f, 0.0f, 1.0f };
			break;
		case kYellow:
			mColor = glm::vec3{ 1.0f, 1.0f, 0.0f };
			break;
		case kMagenta:
			mColor = glm::vec3{ 1.0f, 0.0f, 1.0f };
			break;
		case kCyan:
			mColor = glm::vec3{ 0.0f, 1.0f, 1.0f };
			break;
		case kBlack:
			mColor = glm::vec3{ 0.0f, 0.0f, 0.0f };
			break;
	}

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
		-0.5, 0.0, -0.5,	mColor.x, mColor.y, mColor.z,
		 0.5, 0.0, -0.5,	mColor.x, mColor.y, mColor.z,
		 0.5, 0.0,  0.5,	mColor.x, mColor.y, mColor.z,
		-0.5, 0.0,  0.5,	mColor.x, mColor.y, mColor.z
	};

	const unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2
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