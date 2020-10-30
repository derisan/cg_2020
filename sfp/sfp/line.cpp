#include "line.h"

#include <GL/glew.h>

#include "vertexarray.h"

Line::Line(const glm::vec2& start,
	const glm::vec2& end)
	: mStart{ start },
	mEnd{ end },
	mVertexArray{ nullptr }
{
	Load();
}

Line::~Line()
{
	delete mVertexArray;
}

void Line::Draw()
{
	mVertexArray->SetActive();
	glDrawArrays(GL_LINES, 0, 2);
}

void Line::Load()
{
	const float vertices[] = {			
		mStart.x, mStart.y,
		mEnd.x, mEnd.y
	};

	mVertexArray = new VertexArray{ vertices, 2 };
}