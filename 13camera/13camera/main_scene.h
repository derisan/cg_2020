#pragma once
#include "scene.h"
class MainScene:
    public Scene
{
public:
    MainScene(class Gfw* gfw);

	void Enter() override;
	void Exit() override;
	void ProcessInput(bool* keyState, int x, int y) override;
	void Update() override;
	void Draw() override;

	// Scene specific
	void ResetPosition();
	void PrintMenu();

private:
	class Shader* mMeshShader;
	class Shader* mBgShader;
	class Player* mPlayer;
	class Background* mBackground;
};

