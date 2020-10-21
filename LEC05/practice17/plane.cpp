#include "plane.h"

#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Plane::Plane(Color color)
	: Object{},
	mVertexArray{ nullptr }
{
	Load();
}

Plane::~Plane()
{
	delete mVertexArray;
}

void Plane::Load()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.5, 0.0, -0.5,	color.x, color.y, color.z,
		 0.5, 0.0, -0.5,	color.x, color.y, color.z,
		 0.5, 0.0,  0.5,	color.x, color.y, color.z,
		-0.5, 0.0,  0.5,	color.x, color.y, color.z
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

void Plane::Update(float dt)
{
	Object::Update(dt);
}