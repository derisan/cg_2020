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

private:
	std::vector<class Cube*> mCubes;
};

