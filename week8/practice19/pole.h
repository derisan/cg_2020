#pragma once

#include <vector>

class Pole
{
public:
	Pole();
	~Pole();

	void Update(float dt);
	void Draw(class Shader* shader);
	void Load();

private:
	std::vector<class Cube*> mCubes;
	float mAngle;
};

