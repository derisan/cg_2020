#pragma once

#include <vector>

#include <glm/glm.hpp>

class Game
{
public:
	Game();

	bool Init(int* argc, char** argv, int w = 1024, int h = 768);

	void Run(unsigned char key);
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void SetLightingUniforms();

	void GenerateCubes();
	void GenerateSnows();
	void RemoveSnow(class Actor* actor);

	// Getters
	bool GetShouldClose() const { return mShouldClose; }
	int GetScrWidth() const { return mScrWidth; }
	int GetScrHeight() const { return mScrHeight; }
	std::vector<class Snow*>& GetSnows() { return mSnows; }

	// Setters
	void SetShouldClose(bool value) { mShouldClose = value; }

private:
	void ProcessInput(unsigned char key);
	void Update();
	void Draw();

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	std::vector<class Snow*> mSnows;

	class Renderer* mRenderer;
	class Shader* mPhongShader;

	int mScrWidth;
	int mScrHeight;

	bool mShouldClose;
	bool mIsUpdating;
	bool mIsSnowy;

	glm::vec3 mCameraPos;
};

