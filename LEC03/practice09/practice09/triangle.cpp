#include "triangle.h"

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

Triangle::Triangle()
	: position_{ 0.0f, 0.0f },
	scale_{ 1.0f, 1.0f },
	rotation_{ 0.0f },
	speed_{ 0.005f },
	is_move_{ false },
	is_stretch_{ false },
	should_bounce_{ false },
	angle_{ 0.0f }
{
	forward_ = -glm::vec2{ sin(rotation_), cos(rotation_) };
}

void Triangle::Update()
{
	if (is_move_)
		Move();
	
	if (is_stretch_)
		Stretch();
}

void Triangle::Draw(Shader* shader) 
{
	glm::mat4 trans = glm::identity<glm::mat4>();
	trans = glm::scale(trans, glm::vec3{ scale_, 0.0f });
	trans = glm::rotate(trans, glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::translate(trans, glm::vec3{ position_, 0.0f });

	shader->SetMat4("world", trans);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void Triangle::Move()
{
	position_ += forward_ * speed_;
	
	if (position_.x < -0.75f || position_.x > 0.75f || position_.y < -0.75f || position_.y > 0.75f)
	{
		forward_ *= -1;
		should_bounce_ = true;
	}
	
	if(should_bounce_)
		if (-0.00001f < position_.x && position_.x < 0.00001f && -0.00001f < position_.y && position_.y < 0.00001f)
			forward_ *= -1;
}

void Triangle::Stretch()
{
	auto angle = cos(angle_);
	if (angle < 0)
		angle *= -1;

	if (rotation_ == 0.0f || rotation_ == 180.0f)
		scale_.x = angle;
	else
		scale_.y = angle;

	angle_ += 0.015f;	
}