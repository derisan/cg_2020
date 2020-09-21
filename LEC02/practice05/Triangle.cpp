#include "Triangle.h"
#include <gl/glew.h>

Triangle::Triangle(glm::vec3 world, glm::vec3 color)
	: _world(world.x, world.y, world.z),
	_color(color.x, color.y, color.z),
	_xDir(1),
	_yDir(1),
	_speed(0.03f)
{
}

void Triangle::draw() const
{
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Triangle::move()
{
	_world += glm::vec3(_xDir * _speed * 1.0f, _yDir * _speed * 1.0f, 0.0f);

	if (_world.x > 0.9f || _world.x < -0.9f)
		_xDir *= -1;
	if (_world.y > 0.9f || _world.y < -0.9f)
		_yDir *= -1;
}