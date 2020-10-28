#pragma once

#include <vector>

class House
{
public:
	House();
	~House();

	void Update(float dt);
	void Draw(class Shader* shader);
	void Load();

	bool Collides(class Robot* robot);
private:
	std::vector<class Cube*> mCubes;
};

