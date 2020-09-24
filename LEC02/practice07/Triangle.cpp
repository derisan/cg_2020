#include "Triangle.h"
#include <gl/glew.h>

Triangle::Triangle(glm::vec3 world, glm::vec3 color)
	: _world(world.x, world.y, world.z),
	_color(color.x, color.y, color.z),
	_xDir(1),
	_yDir(1),
	_speed(0.015f),
	_rotation(-90.0f)
{
}

void Triangle::draw() const
{
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Triangle::move()
{
	_world += glm::vec3(_xDir * _speed * 1.0f, _yDir * _speed * 1.0f, 0.0f);

	if (_world.x > 0.90f)
	{
		_xDir *= -1;
		setRotation(-270.0f);
	}

	if (_world.x < -0.90f)
	{
		_xDir *= -1;
		setRotation(-90.0f);
	}

	if (_world.y > 0.90f)
	{
		_yDir *= -1;
		setRotation(-180.0f);
	}

	if (_world.y < -0.90f)
	{
		_yDir *= -1;
		setRotation(0.0f);
	}
}