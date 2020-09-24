#pragma once

#include <glm/glm.hpp>

typedef unsigned int GLenum;

class Circle
{
public:
	enum class State
	{
		kActive,
		kDead
	};

	enum class Destiny
	{
		kAlive,
		kGoHell
	};

	Circle(glm::vec2 center, Destiny destiny);
	~Circle();

	void update();
	void draw(GLenum drawMode) const;
	State getState() const { return state_; }

private:
	class VertexArray* vao_;
	float radius_;
	glm::vec2 center_;
	State state_;
	Destiny destiny_;
};





