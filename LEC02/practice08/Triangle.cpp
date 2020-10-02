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

	if (_border == 0.90f)
		collide();

	if (_world.x > _border)
	{
		_world.x = _border;
		_xDir *= -1;
		setRotation(-270.0f);
		setChangeColor(true);
	}
	else if (_world.x < -_border)
	{
		_world.x = -_border;
		_xDir *= -1;
		setRotation(-90.0f);
		setChangeColor(true);
	}

	if (_world.y > _border)
	{
		_world.y = _border;
		_yDir *= -1;
		setRotation(-180.0f);
		setChangeColor(true);
	}
	else if (_world.y < -_border)
	{
		_world.y = -_border;
		_yDir *= -1;
		setRotation(0.0f);
		setChangeColor(true);
	}
}

void Triangle::collide()
{
	// À­º¯
	if (-0.45f < _world.x && _world.x < 0.45f && 0.40f < _world.y && _world.y < 0.50f)
	{
		_world.y = 0.50f;
		_yDir *= -1;
		auto rot = getRotation();
		rot -= 90.0f;
		setRotation(rot);
		setChangeColor(true);
	}

	// ¾Æ·§º¯
	if (-0.45f < _world.x && _world.x < 0.45f && -0.50f < _world.y && _world.y < -0.40f)
	{
		_world.y = -0.50f;
		_yDir *= -1;
		auto rot = getRotation();
		rot -= 90.0f;
		setRotation(rot);
		setChangeColor(true);
	}

	// ÁÂº¯
	if (-0.50f < _world.x && _world.x < -0.40f && -0.45f < _world.y && _world.y < 0.45f)
	{
		_world.x = -0.50f;
		_xDir *= -1;
		auto rot = getRotation();
		rot -= 90.0f;
		setRotation(rot);
		setChangeColor(true);
	}

	// ¿ìº¯
	if (0.40f < _world.x && _world.x < 0.50f && -0.45f < _world.y && _world.y < 0.45f)
	{
		_world.x = 0.50f;
		_xDir *= -1;
		auto rot = getRotation();
		rot -= 90.0f;
		setRotation(rot);
		setChangeColor(true);
	}

}