#include "pentagon.h"

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "vertexarray.h"

Pentagon::Pentagon()
	: position_{ 0.0f, 0.0f },
	scale_{ 1.0f, 1.0f },
	rotation_{ 0.0f },
	color_{ 0.0f, 0.0f, 0.0f },
	speed_{ 0.005f },
	vao{ nullptr },
	top_x_{ -0.25f },
	top_y_{ 0.25f },
	lefttop_x_{ -0.25f },
	righttop_x_{ 0.25f }
{
	Pull();
}

Pentagon::~Pentagon()
{
	delete vao;
}

void Pentagon::Update()
{
	top_x_ += 0.00125f;
	top_y_ += 0.00125f;

	lefttop_x_ += -0.001f;
	righttop_x_ += 0.001f;

	if (top_x_ > 0.0f)
		top_x_ = 0.0f;

	if (top_y_ > 0.50f)
		top_y_ = 0.50f;

	if (lefttop_x_ < -0.375f)
		lefttop_x_ = -0.375f;

	if (righttop_x_ > 0.375f)
		righttop_x_ = 0.375f;

	Pull();
}

void Pentagon::Draw(Shader* shader)
{
	glm::mat4 trans = glm::identity<glm::mat4>();
	trans = glm::scale(trans, glm::vec3{ scale_, 0.0f });
	trans = glm::rotate(trans, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::translate(trans, glm::vec3{ position_, 0.0f });

	shader->SetMat4("world", trans);
	shader->SetVec3("color", color_);
	vao->SetActive();

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
}

void Pentagon::Pull()
{
	float vertices[] = {
		lefttop_x_, 0.25f, 0.0f,	// left top
		-0.25f, -0.25f, 0.0f,	// left bottom
		0.25f, -0.25f, 0.0f,	// right bottom
		righttop_x_, 0.25f, 0.0f,		// right top
		top_x_, top_y_, 0.0f	// top
	};

	const unsigned int indices[] = {
		0, 1, 2,
		2, 3, 4,
		0, 2, 4
	};

	if (vao)
		delete vao;
	vao = CreateVertexArray(vertices, 5, indices, 9);
}