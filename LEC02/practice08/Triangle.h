#pragma once

#include <glm/glm.hpp>

class Triangle
{
public:
	Triangle(glm::vec3 world = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f), float border = 0.9f);
	void draw() const;
	void move();

	glm::vec3 getWorld() const { return _world; }
	glm::vec3 getColor() const { return _color; }
	
	void setWorld(const glm::vec3& world) { _world = world; }
	void setColor(const glm::vec3& color) { _color = color; }
	void setXDir(int xDir) { _xDir = xDir; }
	void setYDir(int yDir) { _yDir = yDir; }
	
	void setRotation(float rotation) { _rotation = rotation; }
	float getRotation() const { return _rotation; }

	void setChangeColor(bool shouldChangeColor) { _shouldChangeColor = shouldChangeColor; }
	bool getChangeColor() const { return _shouldChangeColor; }
	
private:
	glm::vec3 _world;
	glm::vec3 _color;
	int _xDir;
	int _yDir;
	float _speed;
	float _rotation;
	float _border;
	bool _shouldChangeColor;
};

