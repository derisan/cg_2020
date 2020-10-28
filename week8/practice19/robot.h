#pragma once

#include <vector>

#include <glm/glm.hpp>

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
	void Swing();
	void Reset();

	void SetShouldJump(bool value) { mShouldJump = value; }
	const glm::vec3& GetPos() const;
private:
	std::vector<class Cube*> mCubes;

	// Jump things
	float mJumpSpeed;
	const float mGravity = 0.02f;

	float mAngle;
	float mSpeed;

	bool mShouldJump;
};

