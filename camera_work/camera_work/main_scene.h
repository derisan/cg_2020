#pragma once
#include "scene.h"
class MainScene:
    public Scene
{
public:
    MainScene(class Gfw* gfw);

	void Enter() override;
	void Exit() override;
	void ProcessInput(unsigned char key) override;
	void Update() override;
	void Draw() override;

private:
	class Shader* mMeshShader;
};

