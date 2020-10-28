#pragma once

#include <vector>

class BenchPress
{
public:
	BenchPress();
	~BenchPress();

	void Update(float dt);
	void Draw(class Shader* shader);
	void Load();

	void Move();
private:
	std::vector<class Sphere*> mSpheres;
	std::vector<class Cube*> mCubes;

	float mAngle;
	float mRotationSpeed;
	float mMoveSpeed;
};

