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

private:
	class Shader* mMeshShader;
	class Player* mPlayer;
};

