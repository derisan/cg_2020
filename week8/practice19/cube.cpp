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
			LeftArmLoad();
			break;
		case kRightArm:
			RightArmLoad();
			break;
		case kLeftLeg:
			LeftLegLoad();
			break;
		case kRightLeg:
			RightLegLoad();
			break;
		case kLeftPole:
			LeftPoleLoad();
			break;
		case kRightPole:
			RightPoleLoad();
			break;
		case kBodyPole:
			BodyPoleLoad();
			break;
		case kDefault:
			DefaultLoad();
			break;
	}
}

void Cube::DefaultLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		 -0.5,  0.0,  0.5,	color.x, color.y, color.z,
		 0.5,  0.0,  0.5,	color.x, color.y, color.z,
		 0.5,  1.0,  0.5,	color.x, color.y, color.z,
		-0.5,  1.0,  0.5,	color.x, color.y, color.z,
		-0.5,  0.0, -0.5,	color.x, color.y, color.z,
		 0.5,  0.0, -0.5,	color.x, color.y, color.z,
		 0.5,  1.0, -0.5,	color.x, color.y, color.z,
		-0.5,  1.0, -0.5,	color.x, color.y, color.z,
	};

	const unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2,
		1, 6, 5,
		1, 2, 6,
		5, 6, 7,
		5, 7, 4,
		4, 3, 0,
		7, 3, 4,
		4, 1, 5,
		4, 0, 1,
		3, 6, 2,
		6, 3, 7
	};

	mVertexArray = new VertexArray(vertices, 8, indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
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

void Cube::LeftArmLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.05,  -0.2,  -0.2,	color.x, color.y, color.z,
		 0.05,  -0.2,  -0.2,	color.x, color.y, color.z,
		 0.05,  0.0,  -0.2,	color.x, color.y, color.z,
		-0.05,  0.0,  -0.2,	color.x, color.y, color.z,
		-0.05,  -0.2,  -0.3,	color.x, color.y, color.z,
		 0.05,  -0.2,  -0.3,	color.x, color.y, color.z,
		 0.05,  0.0,  -0.3,	color.x, color.y, color.z,
		-0.05,  0.0,  -0.3,	color.x, color.y, color.z,
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

void Cube::RightArmLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.05,  -0.2,  0.2,	color.x, color.y, color.z,
		 0.05,  -0.2,  0.2,	color.x, color.y, color.z,
		 0.05,  0.0,  0.2,	color.x, color.y, color.z,
		-0.05,  0.0,  0.2,	color.x, color.y, color.z,
		-0.05,  -0.2,  0.3,	color.x, color.y, color.z,
		 0.05,  -0.2,  0.3,	color.x, color.y, color.z,
		 0.05,  0.0,  0.3,	color.x, color.y, color.z,
		-0.05,  0.0,  0.3,	color.x, color.y, color.z,
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

void Cube::LeftLegLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.05,  -0.4,  -0.1,	color.x, color.y, color.z,
		 0.05,  -0.4,  -0.1,	color.x, color.y, color.z,
		 0.05,  0.0,   -0.1,	color.x, color.y, color.z,
		-0.05,  0.0,   -0.1,	color.x, color.y, color.z,
		-0.05,  -0.4,  -0.05,	color.x, color.y, color.z,
		 0.05,  -0.4,  -0.05,	color.x, color.y, color.z,
		 0.05,  0.0,   -0.05,	color.x, color.y, color.z,
		-0.05,  0.0,   -0.05,	color.x, color.y, color.z,
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

void Cube::RightLegLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.05,  -0.4,  0.05,	color.x, color.y, color.z,
		 0.05,  -0.4,  0.05,	color.x, color.y, color.z,
		 0.05,  0.0,   0.05,	color.x, color.y, color.z,
		-0.05,  0.0,   0.05,	color.x, color.y, color.z,
		-0.05,  -0.4,  0.1,	color.x, color.y, color.z,
		 0.05,  -0.4,  0.1,	color.x, color.y, color.z,
		 0.05,  0.0,   0.1,	color.x, color.y, color.z,
		-0.05,  0.0,   0.1,	color.x, color.y, color.z,
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

void Cube::LeftPoleLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.05,  -0.4,  -0.1,	color.x, color.y, color.z,
		 0.05,  -0.4,  -0.1,	color.x, color.y, color.z,
		 0.05,  0.0,   -0.1,	color.x, color.y, color.z,
		-0.05,  0.0,   -0.1,	color.x, color.y, color.z,
		-0.05,  -0.4,  -0.05,	color.x, color.y, color.z,
		 0.05,  -0.4,  -0.05,	color.x, color.y, color.z,
		 0.05,  0.0,   -0.05,	color.x, color.y, color.z,
		-0.05,  0.0,   -0.05,	color.x, color.y, color.z,
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

void Cube::RightPoleLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.05,  -0.4,  0.05,	color.x, color.y, color.z,
		 0.05,  -0.4,  0.05,	color.x, color.y, color.z,
		 0.05,  0.0,   0.05,	color.x, color.y, color.z,
		-0.05,  0.0,   0.05,	color.x, color.y, color.z,
		-0.05,  -0.4,  0.1,	color.x, color.y, color.z,
		 0.05,  -0.4,  0.1,	color.x, color.y, color.z,
		 0.05,  0.0,   0.1,	color.x, color.y, color.z,
		-0.05,  0.0,   0.1,	color.x, color.y, color.z,
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

void Cube::BodyPoleLoad()
{
	glm::vec3 color{ GetColor() };

	const float vertices[] = {
		// pos				// color
		-0.05,  -0.8,  -0.3,	color.x, color.y, color.z,
		 0.05,  -0.8,  -0.3,	color.x, color.y, color.z,
		 0.05,  -0.4,   -0.3,	color.x, color.y, color.z,
		-0.05,  -0.4,   -0.3,	color.x, color.y, color.z,
		-0.05,  -0.8,  0.3,	color.x, color.y, color.z,
		 0.05,  -0.8,  0.3,	color.x, color.y, color.z,
		 0.05,  -0.4,   0.3,	color.x, color.y, color.z,
		-0.05,  -0.4,   0.3,	color.x, color.y, color.z,
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