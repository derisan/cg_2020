#include "main_scene.h"

#include <iostream>

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
#include "box_component.h"
#include "Background.h"
#include "tree.h"


MainScene::MainScene(Gfw* gfw)
	: Scene{ gfw },
	mMeshShader{ nullptr },
	mBgShader{ nullptr },
	mPlayer{ nullptr },
	mBackground{ nullptr }
{
	mMeshShader = Renderer::Get()->GetShader("mesh");
	mBgShader = Renderer::Get()->GetShader("bg");

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(mGfw->GetScrWidth()) / mGfw->GetScrHeight(),
		0.1f, 100.0f);
	mMeshShader->SetActive();
	mMeshShader->SetMatrix4Uniform("uProj", proj);
}


void MainScene::Enter()
{
	mPlayer = new Player{ mGfw };
	mBackground = new Background{ "Assets/bg.jpg" };
	
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

	auto tree = new Tree{ mGfw };
	tree->SetPosition(glm::vec3{ -6.0f, -1.0, -6.0f });
	tree = new Tree{ mGfw };
	tree->SetPosition(glm::vec3{ 6.0f, -1.0, -6.0f });
	tree = new Tree{ mGfw };
	tree->SetPosition(glm::vec3{ -6.0f, -1.0, -12.0f });
	tree = new Tree{ mGfw };
	tree->SetPosition(glm::vec3{ 6.0f, -1.0, -12.0f });

	PrintMenu();
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
	else if (keyState[114]) // r
		ResetPosition();
}

void MainScene::Update()
{
	const auto& robots = mGfw->GetActorsAt(Gfw::Layer::kRobot);
	const auto& trees = mGfw->GetActorsAt(Gfw::Layer::kObstacle);

	for (auto robot : robots)
	{
		auto rp = (Robot*)robot;
		const auto& robotBox = rp->GetBox()->GetWorldBox();
		for(auto tree : trees)
		{
			auto tp = (Tree*)tree;

			const auto& treeBox = tp->GetBox()->GetWorldBox();
			if (Intersects(robotBox, treeBox))
				rp->ChangeDirection();
		}
	}
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

	mBgShader->SetActive();
	mBackground->Draw();

	glutSwapBuffers();
}

void MainScene::ResetPosition()
{
	const auto& players = mGfw->GetActorsAt(Gfw::Layer::kPlayer);
	const auto& robots = mGfw->GetActorsAt(Gfw::Layer::kRobot);

	for (auto player : players)
		player->SetPosition(glm::vec3{ 0.0f, -1.0f, 0.0f });

	robots[0]->SetPosition(glm::vec3{ -9.0f, -1.0f, -9.0f });
	robots[1]->SetPosition(glm::vec3{ -4.5f, -1.0f, -9.0f });
	robots[2]->SetPosition(glm::vec3{ 4.5f, -1.0f, -9.0f });
	robots[3]->SetPosition(glm::vec3{ 9.0f, -1.0f, -9.0f });
}

void MainScene::PrintMenu()
{
	std::cout << "--------------------명령어--------------------" << std::endl;
	std::cout << "ESC	프로그램 종료" << std::endl;
	std::cout << "숫자 1	1인칭 시점으로 변경" << std::endl;
	std::cout << "숫자 3	3인칭 시점으로 변경" << std::endl;
	std::cout << "WASD	각 시점에 따른 이동" << std::endl;
	std::cout << "R	로봇과 플레이어 위치 초기화" << std::endl;
	std::cout << "마우스	1인칭 시점에서 좌우로 시야 회전" << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
}