#pragma once

#include "object.h"

#include <GL/glew.h>

class Pyramid : public Object
{
public:
	Pyramid();
	~Pyramid();

	void Load();

	void Update(float dt) override;
	void Draw(class Shader* shader) override;

private:
	class VertexArray* mVertexArray;
	float mAngle;
};

