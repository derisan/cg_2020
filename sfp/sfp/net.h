#pragma once

#include <vector>
#include <array>

#include "object.h"

class Net
{
public:
	Net(int w, int h, class Game* game);
	~Net();

	void Update(std::vector<class Object*>& objs);
	void Draw();

	void CheckCollision(std::vector<class Object*>& objs);
	void Reposition(class Object* obj);
	void MouseReposition(class Object* obj, const glm::vec2& pos);

	void MakeMesh();

	int IsOver() const { return mCount == 24; }

private:
	class Game* mGame;

	std::vector<class Line*> mLines;
	
	int mScrWidth;
	int mScrHeight;
	float mBorder;
	int mCount;

	std::array<bool, 24> mVisited;
};

