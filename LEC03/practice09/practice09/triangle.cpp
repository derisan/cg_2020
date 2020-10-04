#include "triangle.h"

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

Triangle::Triangle()
	: position_{ 0.0f, 0.0f },
	scale_{ 1.0f, 1.0f },
	rotation_{ 0.0f },
	color_{ 0.0f, 0.0f, 0.0f },
	speed_{ 5.0f },
	is_move_{ false },
	is_stretch_{ false }
{
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
	shader->SetVec3("color", color_);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void Triangle::Move()
{

}

void Triangle::Stretch()
{

}