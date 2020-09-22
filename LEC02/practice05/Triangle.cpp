#include "Triangle.h"
#include <gl/glew.h>

Triangle::Triangle(glm::vec3 world, glm::vec3 color, float x, float y)
	: _world(world.x, world.y, world.z),
	_color(color.x, color.y, color.z),
	_xDir(1),
	_yDir(0),
	_speed(0.03f),
	_border{x, y}
{
}

void Triangle::draw() const
{
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Triangle::move()
{
	_world += glm::vec3(_xDir * _speed * 1.0f, _yDir * _speed * 1.0f, 0.0f);

	if (_world.x > 0.88f )
	{
		_world.x = 0.88f;
		_xDir = 0;
		_yDir = 1;
	}

	if (_world.y > 0.88f)
	{
		_world.y = 0.88f;
		_xDir = -1;
		_yDir = 0;
	}

	if (_world.x < _border.x)
	{
		_world.x = _border.x;
		_xDir = 0;
		_yDir = -1;
	}

	if (_world.y < _border.y)
	{
		_world.y = _border.y;
		_xDir = 1;
		_yDir = 0;
	}
}