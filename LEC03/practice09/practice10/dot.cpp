#include "dot.h"

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "vertexarray.h"

Dot::Dot()
	: position_{ 0.0f, 0.0f },
	scale_{ 1.0f, 1.0f },
	rotation_{ 0.0f },
	color_{ 0.0f, 0.0f, 0.0f },
	speed_{ 0.005f },
	vao{ nullptr }
{
	Pull();
}

Dot::~Dot()
{
	delete vao;
}

void Dot::Update()
{
	scale_.x -= 0.004f;
	scale_.y -= 0.004f;

	if (scale_.x < 0.05f)
		scale_.x = 0.05f;
	if (scale_.y < 0.05f)
		scale_.y = 0.05f;
}

void Dot::Draw(Shader* shader)
{
	glm::mat4 trans = glm::identity<glm::mat4>();
	trans = glm::translate(trans, glm::vec3{ position_, 0.0f });
	trans = glm::rotate(trans, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3{ scale_, 0.0f });

	shader->SetMat4("world", trans);
	shader->SetVec3("color", color_);
	vao->SetActive();

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
}

void Dot::Pull()
{
	float vertices[] = {
		-0.375f, 0.25f, 0.0f,	// left top
		-0.25f, -0.25f, 0.0f,	// left bottom
		0.25f, -0.25f, 0.0f,	// right bottom
		0.375f, 0.25f, 0.0f,	// right top
		0.0f, 0.5f, 0.0f		// top
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