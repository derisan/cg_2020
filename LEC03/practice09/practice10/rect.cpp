#include "rect.h"

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "vertexarray.h"

Rect::Rect()
	: position_{ 0.0f, 0.0f },
	scale_{ 1.0f, 1.0f },
	rotation_{ 0.0f },
	color_{ 0.0f, 0.0f, 0.0f },
	speed_{ 0.005f },
	vao{ nullptr },
	left_x_{ 0.0f },
	right_x_{ 0.0f }
{
	Pull();
}

Rect::~Rect()
{
	delete vao;
}

void Rect::Update()
{
	left_x_ += -0.00125f;
	right_x_ += 0.00125f;

	if (left_x_ < -0.25f)
		left_x_ = -0.25f;

	if (right_x_ > 0.25f)
		right_x_ = 0.25f;

	Pull();
}

void Rect::Draw(Shader* shader)
{
	glm::mat4 trans = glm::identity<glm::mat4>();
	trans = glm::scale(trans, glm::vec3{ scale_, 0.0f });
	trans = glm::rotate(trans, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::translate(trans, glm::vec3{ position_, 0.0f });

	shader->SetMat4("world", trans);
	shader->SetVec3("color", color_);
	vao->SetActive();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Rect::Pull()
{
	float vertices[] = {
		left_x_, 0.25f, 0.0f,		// left top
		-0.25f, -0.25f, 0.0f,	// left bottom
		0.25f, -0.25f, 0.0f,	// right bottom
		right_x_, 0.25f, 0.0f			// right top
	};

	const unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	if (vao)
		delete vao;
	vao = CreateVertexArray(vertices, 4, indices, 6);
}