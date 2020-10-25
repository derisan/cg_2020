#pragma once

#include <vector>

class Robot
{
public:
	Robot();
	~Robot();

	void Update(float dt);
	void Draw(class Shader* shader);
	void Load();

	// Program specific
	void Jump();
	void Move(unsigned char key);

	void SetShouldJump(bool value) { mShouldJump = value; }
private:
	std::vector<class Cube*> mCubes;

	float mJumpSpeed;
	const float mGravity = 0.02f;

	bool mShouldJump;
};

