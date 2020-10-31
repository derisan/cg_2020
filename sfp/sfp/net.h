#pragma once

#include <vector>

class Net
{
public:
	Net(int w, int h, class Game* game);
	~Net();

	void Update(std::vector<class Object*>& objs);
	void Draw();

	void CheckCollision(std::vector<class Object*>& objs);

	void MakeMesh();

private:
	class Game* mGame;

	std::vector<class Line*> mLines;
	
	int mScrWidth;
	int mScrHeight;

	float mBorder;
};

