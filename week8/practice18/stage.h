#pragma once

#include <vector>

class Stage
{
public:
	Stage();
	~Stage();

	void Update(float dt);
	void Draw(class Shader* shader);
	void Load();

	// Setters
	void SetShouldOpenFront(bool value) { mShouldOpenFront = value; }

	// Program specific
	void Slide();

private:
	std::vector<class Plane*> mPlanes;
	int mFrontIdx;

	bool mShouldOpenFront;
};

