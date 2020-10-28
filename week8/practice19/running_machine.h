#pragma once

#include <vector>

class RunningMachine
{
public:
	RunningMachine();
	~RunningMachine();

	void Update(float dt);
	void Draw(class Shader* shader);
	void Load();

private:
	std::vector<class Cube*> mCubes;
	class Cylinder* cylinder;
	float mAngle;
	float mSpeed;
};

