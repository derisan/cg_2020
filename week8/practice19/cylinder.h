#pragma once

#include <vector>

#include "object.h"

class Cylinder :
	public Object
{
public:
	Cylinder(Color color = Object::kBlack);
	~Cylinder();

	void Update(float dt) override;
	void Draw(class Shader* shader) override;
	void Load() override;

	std::vector<float> getUnitCircleVertices();
	

private:
	class VertexArray* mVertexArray;
};

