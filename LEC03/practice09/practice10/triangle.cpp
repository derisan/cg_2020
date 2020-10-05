#include "triangle.h"

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "vertexarray.h"

Triangle::Triangle()
	: position_{ 0.0f, 0.0f },
	scale_{ 1.0f, 1.0f },
	rotation_{ 0.0f },
	color_{ 0.0f, 0.0f, 0.0f },
	speed_{ 0.005f },
	vao{ nullptr },
	x_{ 0.0f },
	y_{ 0.25f }
{
	Pull();
}

Triangle::~Triangle()
{
	delete vao;
}

void Triangle::Update()
{
	x_ += 0.00125f;
	y_ += -0.0025f;

	if (x_ > 0.25f)
		x_ = 0.25f;

	if (y_ < -0.25f)
		y_ = -0.25f;

	Pull();
}

void Triangle::Draw(Shader* shader) 
{
	glm::mat4 trans = glm::identity<glm::mat4>();
	trans = glm::translate(trans, glm::vec3{ position_, 0.0f });
	trans = glm::rotate(trans, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3{ scale_, 0.0f });

	shader->SetMat4("world", trans);
	shader->SetVec3("color", color_);
	vao->SetActive();

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void Triangle::Pull()
{
	float vertices[] = {
		0.0f, 0.25f, 0.0f,
		-0.25f, -0.25f, 0.0f,
		x_, y_, 0.0f
	};

	const unsigned int indices[] = {
		0, 1, 2
	};

	if (vao)
		delete vao;
	vao = CreateVertexArray(vertices, 3, indices, 3);
}