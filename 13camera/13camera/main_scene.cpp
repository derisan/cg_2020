#include "main_scene.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gfw.h"
#include "renderer.h"
#include "shader.h"
#include "robot.h"
#include "player.h"
#include "mesh_component.h"


MainScene::MainScene(Gfw* gfw)
	: Scene{ gfw },
	mMeshShader{ nullptr },
	mPlayer{ nullptr }
{
	mMeshShader = Renderer::Get()->GetShader("mesh");

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(mGfw->GetScrWidth()) / mGfw->GetScrHeight(),
		0.1f, 100.0f);
	mMeshShader->SetActive();
	mMeshShader->SetMatrix4Uniform("uProj", proj);
}


void MainScene::Enter()
{
	mPlayer = new Player{ mGfw };
	
	for (int i = 0; i < 10; ++i)
	{
		auto plane = new Actor{ mGfw };
		plane->SetPosition(glm::vec3{ 0.0f, -1.1f, -2.0f * i });
		auto mc = new MeshComponent{ plane, "Assets/road.gpmesh" };
	}

	auto robot = new Robot{ mGfw };
	robot->SetPosition(glm::vec3{ -9.0f, -1.0f, -9.0f });
	robot = new Robot{ mGfw };
	robot->SetPosition(glm::vec3{ -4.5f, -1.0f, -9.0f });
	robot = new Robot{ mGfw };
	robot->SetPosition(glm::vec3{ 4.5f, -1.0f, -9.0f });
	robot = new Robot{ mGfw };
	robot->SetPosition(glm::vec3{ 9.0f, -1.0f, -9.0f });
}

void MainScene::Exit()
{
	mGfw->RemoveAllActors();
}

void MainScene::ProcessInput(bool* keyState, int x, int y)
{
	if (keyState[49]) // Numpad 1
		mPlayer->SetViewOption(Player::ViewOption::kFPS);
	else if (keyState[51]) // Numpad 3
		mPlayer->SetViewOption(Player::ViewOption::kFollow);
}

void MainScene::Update()
{

}

void MainScene::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	mMeshShader->SetActive();
	const auto& view = mPlayer->GetView();
	mMeshShader->SetMatrix4Uniform("uView", view);
	for (auto mesh : mGfw->GetMeshes())
		mesh->Draw(mMeshShader);

	glutSwapBuffers();
}