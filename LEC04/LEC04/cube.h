#pragma once

#include "object.h"

#include <GL/glew.h>

class Cube : public Object
{
public:
	Cube();
	~Cube();

	void Load();

	void Update(float dt) override;
	void Draw(class Shader* shader) override;

private:
	class VertexArray* mVertexArray;

	
};

