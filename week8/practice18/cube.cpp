#include "cube.h"

#include <GL/glew.h>

#include "vertexarray.h"
#include "shader.h"

Cube::Cube(Part part, Color color)
	: Object{color},
	mPart{ part },
	mVertexArray{ nullptr }
{
	Load();
}

Cube::~Cube()
{
	delete mVertexArray;
}

void Cube::Update(float dt)
{
	Object::Update(dt);
}

void Cube::Draw(Shader* shader)
{
	shader->SetActive();
	shader->SetMatrixUniform("uWorld", GetWorldTransform());
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}

void Cube::Load()
{
	switch (mPart)
	{
		case kHead:
			HeadLoad();
			break;
		case kNose:
			NoseLoad();
			break;
		case kBody:
			BodyLoad();
			break;
		case kLeftArm:
			break;
		case kRightArm:
			break;
		case kLeftLeg:
			break;
		case kRightLeg:
			break;
	}

	//const float vertices[] = {
	//	// pos				// color
	//	 -0.5,  0.0,  0.5,	color.x, color.y, color.z,
	//	 0.5,  0.0,  0.5,	color.x, color.y, color.z,
	//	 0.5,  1.0,  0.5,	color.x, color.y, color.z,
	//	-0.5,  1.0,  0.5,	color.x, color.y, color.z,
	//	-0.5,  0.0, -0.5,	color.x, color.y, color.z,
	//	 0.5,  0.0, -0.5,	color.x, color.y, color.z,
	//	 0.5,  1.0, -0.5,	color.x, color.y, color.z,
	//	-0.5,  1.0, -0.5,	color.x, color.y, color.z,
	//};

	//const unsigned int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0,
	//	1, 5, 6,
	//	6, 2, 1,
	//	7, 6, 5,
	//	5, 4, 7,
	//	4, 0, 3,
	//	3, 7, 4,
	//	4, 5, 1,
	//	1, 0, 4,
	//	3, 2, 6,
	//	6, 7, 3
	//};
}

void Cube::HeadLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		 -0.1,  0.6,  0.1,	color.x, color.y, color.z,
		 0.1,  0.6,  0.1,	color.x, color.y, color.z,
		 0.1,  0.8,  0.1,	color.x, color.y, color.z,
		-0.1,  0.8,  0.1,	color.x, color.y, color.z,
		-0.1,  0.6, -0.1,	color.x, color.y, color.z,
		 0.1,  0.6, -0.1,	color.x, color.y, color.z,
		 0.1,  0.8, -0.1,	color.x, color.y, color.z,
		-0.1,  0.8, -0.1,	color.x, color.y, color.z,
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

void Cube::NoseLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		 0.1,  0.65,  0.05,	color.x, color.y, color.z,
		 0.15,  0.65,  0.05,	color.x, color.y, color.z,
		 0.15,  0.75,  0.05,	color.x, color.y, color.z,
		0.1,  0.75,  0.05,	color.x, color.y, color.z,
		0.1,  0.65, -0.05,	color.x, color.y, color.z,
		 0.15,  0.65, -0.05,	color.x, color.y, color.z,
		 0.15,  0.75, -0.05,	color.x, color.y, color.z,
		0.1,  0.75, -0.05,	color.x, color.y, color.z,
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

void Cube::BodyLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		 -0.2,  0.4,  0.2,	color.x, color.y, color.z,
		 0.2,  0.4,  0.2,	color.x, color.y, color.z,
		 0.2,  0.6,  0.2,	color.x, color.y, color.z,
		-0.2,  0.6,  0.2,	color.x, color.y, color.z,
		-0.2,  0.4, -0.2,	color.x, color.y, color.z,
		 0.2,  0.4, -0.2,	color.x, color.y, color.z,
		 0.2,  0.6, -0.2,	color.x, color.y, color.z,
		-0.2,  0.6, -0.2,	color.x, color.y, color.z,
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