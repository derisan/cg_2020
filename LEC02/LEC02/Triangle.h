#pragma once

#include <glm/glm.hpp>

class Triangle
{
public:
	Triangle(glm::vec3 world = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f));
	void draw() const;
	glm::vec3 getWorld() const { return _world; }
	glm::vec3 getColor() const { return _color; }
	void setWorld(const glm::vec3& world) { _world = world; }

private:
	glm::vec3 _world;
	glm::vec3 _color;
};

