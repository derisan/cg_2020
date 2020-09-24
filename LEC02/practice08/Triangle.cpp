#include "Triangle.h"
#include <gl/glew.h>

Triangle::Triangle(glm::vec3 world, glm::vec3 color, glm::vec3 scale, float border)
	: _world(world.x, world.y, world.z),
	_color(color.x, color.y, color.z),
	_scale(scale.x, scale.y, scale.z),
	_xDir(1),
	_yDir(1),
	_speed(0.015f),
	_rotation(-90.0f),
	_border(border),
	_shouldChangeColor(false)
{
}

void Triangle::draw() const
{
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Triangle::move()
{
	_world += glm::vec3(_xDir * _speed * 1.0f, _yDir * _speed * 1.0f, 0.0f);

	if (_world.x > _border)
	{
		_xDir *= -1;
		setRotation(-270.0f);
		setChangeColor(true);
	}

	if (_world.x < -_border)
	{
		_xDir *= -1;
		setRotation(-90.0f);
		setChangeColor(true);
	}

	if (_world.y > _border)
	{
		_yDir *= -1;
		setRotation(-180.0f);
		setChangeColor(true);
	}

	if (_world.y < -_border)
	{
		_yDir *= -1;
		setRotation(0.0f);
		setChangeColor(true);
	}
}