#include "orbit.h"

#include <vector>

#include <GL/glew.h>

#include "shader.h"
#include "vertexarray.h"

Orbit::Orbit()
	: Object{},
	mVertexArray{ nullptr }
{
	Load();
}

Orbit::~Orbit()
{
	delete mVertexArray;
}

void Orbit::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawArrays(GL_LINE_STRIP, 0, 360);
}

void Orbit::Load()
{
	std::vector<float> vertices;
	vertices.reserve(2160);

	for (float i = 0.0f; i < 360.0f; i += 1.0f)
	{
		vertices.push_back(cos(glm::radians(i)));
		vertices.push_back(0);
		vertices.push_back(sin(glm::radians(i)));
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
	}

	mVertexArray = new VertexArray(vertices.data(), vertices.size() / 6);
}