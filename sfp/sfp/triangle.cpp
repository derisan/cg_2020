#include "triangle.h"

#include <gl/glew.h>

#include "vertexarray.h"
#include "shader.h"

Triangle::Triangle()
	: Object{}
{
	Load();
}

Triangle::~Triangle()
{
	delete mVertexArray;
}

void Triangle::Update(float dt)
{
	Object::Update(dt);
}

void Triangle::Draw(Shader* shader)
{
	Object::Draw(shader);
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), 
		GL_UNSIGNED_INT, nullptr);
}

void Triangle::Load()
{
	const float vertices[] = {
		// pos				
		-0.25, -0.25, 0.0,	
		 0.25, -0.25, 0.0,	
		 0.0, 0.25, 0.0	
	};

	const unsigned int indices[] = {
		0, 1, 2,
	};

	mVertexArray = new VertexArray(vertices, sizeof(vertices) / sizeof(float), 
		indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
}