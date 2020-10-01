#include <cmath>
#include <gl/glew.h>

#include "Circle.h"
#include "VertexArray.h"

Circle::Circle(glm::vec2 center, Destiny destiny)
	: vao_{ nullptr },
	radius_{ 0.0f },
	center_{ center },
	state_{ State::kActive },
	destiny_{ destiny },
	num_points_{ 0 }
{

}

Circle::~Circle()
{
	delete vao_;
}

void Circle::update()
{
	if (num_points_ >= 360)
		if (destiny_ == Destiny::kAlive)
			num_points_ = 0;
		
		else
			state_ = State::kDead;

	if (getState() == State::kActive)
	{
		float verts[360];
		for (int i = 0; i < num_points_; i += 3)
		{
			radius_ += 0.005f;
			float theta = i  * 20.0f / 3.14f;
			verts[i] = center_.x + radius_ * cos(theta);
			verts[i + 1] = center_.y + radius_ * sin(theta);
			verts[i + 2] = 0;
		}

		if (vao_)
			delete vao_;
		vao_ = createVertexArray(verts, 120);

		radius_ = 0.0f;
		num_points_ += 3;
	}
}

void Circle::draw(GLenum drawMode) const
{
	if (getState() == State::kActive)
	{
		vao_->use();
		glDrawArrays(drawMode, 0, 120);
	}
}