#pragma once

#include <glm/glm.hpp>


class Game
{
public:
	Game(int w, int h);
	~Game();

	bool Init(int* argc, char** argv);
	void LoadData();
	void Shutdown();
	
	// Event handling
	void ProcessKeyboardInput(unsigned char key);
	void ProcessMouseInput(int button, int state, int x, int y);
	void Update();
	void Draw();

	void ChangeDrawMode();

	void CreateCutter();
	void DeleteCutter();

	// Setters
	void SetShouldPause(bool value) { mShouldPause = value; }

	// Getters
	bool GetShouldEnd() const { return mShouldEnd; }

private:
	const int mScrWidth;
	const int mScrHeight;
	
	class Shader* mShader;
	class Line* mCutter;

	glm::vec2 mCutterStartPos;
	glm::vec2 mCutterEndPos;

	class ObjectManager* mObjManager;
	class Net* mNet;

	unsigned int mDrawMode;
	bool mShouldPause;
	bool mShouldEnd;
};

