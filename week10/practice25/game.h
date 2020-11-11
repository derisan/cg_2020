#pragma once

#include <vector>

class Game
{
public:
	Game();

	bool Init(int* argc, char** argv, int w = 1024, int h = 768);

	void Run(unsigned char key);
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void GenerateCube();
	void GeneratePyramid();
	void ChangeDrawings();

	// Getters
	bool GetShouldClose() const { return mShouldClose; }
	int GetScrWidth() const { return mScrWidth; }
	int GetScrHeight() const { return mScrHeight; }

	// Setters
	void SetShouldClose(bool value) { mShouldClose = value; }

private:
	void ProcessInput(unsigned char key);
	void Update();
	void Draw();

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class Shader* mMeshShader;
	class Background* mBackground;

	int mScrWidth;
	int mScrHeight;

	bool mShouldClose;
	bool mIsUpdating;
	bool mIsCube;
};

