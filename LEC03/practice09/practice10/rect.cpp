#include "rect.h"

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

#include "shader.h"
#include "vertexarray.h"

Rect::Rect()
	: position_{ 0.0f, 0.0f },
	scale_{ 1.0f, 1.0f },
	rotation_{ 0.0f },
	color_{ 0.0f, 0.0f, 0.0f },
	speed_{ 0.005f },
	vao_{ nullptr },
	lefttop_{ -0.25f, 0.25f },
	righttop_{ 0.25f, 0.25f },
	leftbot_{ -0.25f, -0.25f },
	rightbot_{ 0.25f, -0.25f }
{
	UpdateVAO();
}

Rect::~Rect()
{
	delete vao_;
}

void Rect::Update(const glm::vec2& pos)
{
	NearVertex(pos);

	UpdateVAO();
}

void Rect::Draw(Shader* shader)
{
	glm::mat4 trans = glm::identity<glm::mat4>();
	trans = glm::translate(trans, glm::vec3{ position_, 0.0f });
	trans = glm::rotate(trans, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3{ scale_, 0.0f });

	shader->SetMat4("world", trans);
	shader->SetVec3("color", color_);
	vao_->SetActive();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Rect::UpdateVAO()
{
	float vertices[] = {
		lefttop_.x, lefttop_.y, 0.0f,		// left top
		leftbot_.x, leftbot_.y, 0.0f,	// left bottom
		rightbot_.x, rightbot_.y, 0.0f,	// right bottom
		righttop_.x, righttop_.y, 0.0f			// right top
	};

	const unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	if (vao_)
		delete vao_;
	vao_ = CreateVertexArray(vertices, 4, indices, 6);
}

void Rect::NearVertex(const glm::vec2& pos)
{
	if (glm::distance(pos, lefttop_) < 0.1f)
	{
		lefttop_.x = pos.x;
		lefttop_.y = pos.y;
	}

	else if (glm::distance(pos, righttop_) < 0.1f)
	{
		righttop_.x = pos.x;
		righttop_.y = pos.y;
	}

	else if (glm::distance(pos, leftbot_) < 0.1f)
	{
		leftbot_.x = pos.x;
		leftbot_.y = pos.y;
	}

	else if (glm::distance(pos, rightbot_) < 0.1f)
	{
		rightbot_.x = pos.x;
		rightbot_.y = pos.y;
	}

}