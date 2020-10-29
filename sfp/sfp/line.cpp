#include "line.h"

#include <iostream>

#include <gl/glew.h>

#include "vertexarray.h"
#include "shader.h"

Line::Line(const glm::vec3& start, const glm::vec3& end)
	: Object{},
	mVertexArray{ nullptr },
	mStart{ start },
	mEnd{ end }
{
	Load();
}

Line::~Line()
{
	delete mVertexArray;
}

void Line::Update(float dt)
{
	Object::Update(dt);
}

void Line::Draw(Shader* shader)
{
	Object::Draw(shader);
	mVertexArray->SetActive();
	glDrawArrays(GL_LINES, 0, 2);
}

void Line::Load()
{
	const float vertices[] = {
		// pos				
		mStart.x, mStart.y, 0.0f,
		mEnd.x, mEnd.y, 0.0f
	};

	mVertexArray = new VertexArray{ vertices, 2 };
}