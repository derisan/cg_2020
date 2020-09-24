#include <cmath>
#include <gl/glew.h>

#include "Circle.h"
#include "VertexArray.h"

Circle::Circle(glm::vec2 center, Destiny destiny)
	: vao_{ nullptr },
	radius_{ 0.0f },
	center_{ center },
	state_{ State::kActive },
	destiny_{ destiny }
{

}

Circle::~Circle()
{
	delete vao_;
}

void Circle::update()
{
	radius_ += 0.005f;
	if (radius_ > 1.0f)
		if (destiny_ == Destiny::kAlive)
			radius_ = 0.0f;
		else
			state_ = State::kDead;

	if (getState() == State::kActive)
	{
		float verts[360];
		for (int i = 0; i < 360; i += 3)
		{
			float theta = i * 3.141592 / 180;
			verts[i] = center_.x + radius_ * cos(theta);
			verts[i + 1] = center_.y + radius_ * sin(theta);
			verts[i + 2] = 0;
		}

		if (vao_)
			delete vao_;
		vao_ = createVertexArray(verts, 120);
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