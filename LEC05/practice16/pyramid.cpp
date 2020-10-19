#include "pyramid.h"

#include "vertexarray.h"

Pyramid::Pyramid(Side side)
	: Plane{},
	mSide{ side }
{
	Load();
}

void Pyramid::Load()
{
	switch (mSide)
	{
		case kFront:
			CreateFront();
			break;
		case kLeft:
			CreateLeft();
			break;
		case kRight:
			CreateRight();
			break;
		case kBack:
			CreateBack();
			break;
	}
}

void Pyramid::CreateFront()
{
	const float vertices[] = {
		// pos				// color
		 0.0, 0.0, -0.5,	1.0, 0.0, 0.0,
		 0.0, 0.0,  0.5,	1.0, 0.0, 0.0,
		 0.5, 1.0,  0.0,	1.0, 0.0, 0.0
	};

	const unsigned int indices[] = {
		0, 1, 2,
	};


	auto vertexArray = new VertexArray(vertices, 3,
		indices, 3);

	SetVertexArray(vertexArray);
}

void Pyramid::CreateBack()
{
	const float vertices[] = {
		// pos				// color
		 0.0, 0.0, -0.5,	0.0, 1.0, 0.0,
		 0.0, 0.0,  0.5,	0.0, 1.0, 0.0,
		-0.5, 1.0,  0.0,	0.0, 1.0, 0.0
	};

	const unsigned int indices[] = {
		0, 2, 1,
	};


	auto vertexArray = new VertexArray(vertices, 3,
		indices, 3);

	SetVertexArray(vertexArray);
}

void Pyramid::CreateLeft()
{
	const float vertices[] = {
		// pos				// color
		-0.5, 0.0,  0.0,	1.0, 1.0, 0.0,
		 0.5, 0.0,  0.0,	1.0, 1.0, 0.0,
		 0.0, 1.0,  0.5,	1.0, 1.0, 0.0
	};

	const unsigned int indices[] = {
		0, 2, 1,
	};

	auto vertexArray = new VertexArray(vertices, 3,
		indices, 3);

	SetVertexArray(vertexArray);
}

void Pyramid::CreateRight()
{
	const float vertices[] = {
		// pos				// color
		-0.5, 0.0,  0.0,	0.0, 0.0, 1.0,
		 0.5, 0.0,  0.0,	0.0, 0.0, 1.0,
		 0.0, 1.0,  -0.5,	0.0, 0.0, 1.0
	};

	const unsigned int indices[] = {
		0, 1, 2,
	};


	auto vertexArray = new VertexArray(vertices, 3,
		indices, 3);

	SetVertexArray(vertexArray);
}