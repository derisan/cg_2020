#include "game.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.h"
#include "shader.h"
#include "plane.h"
#include "pyramid.h"
#include "background.h"

Game::Game()
	: mRenderer{ nullptr },
	mMeshShader{ nullptr },
	mScrWidth{ 0 },
	mScrHeight{ 0 },
	mShouldClose{ false },
	mIsUpdating{ false },
	mIsCube{ true }
{

}

bool Game::Init(int* argc, char** argv, int w, int h)
{
	mScrWidth = w;
	mScrHeight = h;

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(mScrWidth, mScrHeight);
	glutCreateWindow("Practice 23");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize GLEW" << std::endl;
		return false;
	}

	mRenderer = Renderer::Get();
	mMeshShader = mRenderer->GetShader("mesh");
	mMeshShader->SetActive();
	glm::mat4 view{ 1.0f };
	view = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 3.0f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(mScrWidth) / mScrHeight, 0.1f, 100.0f);
	mMeshShader->SetMatrix4Uniform("uView", view);
	mMeshShader->SetMatrix4Uniform("uProj", proj);

	GenerateCube();

	new Background{ this };
	
	return true;
}

void Game::Run(unsigned char key)
{
	if (!mShouldClose)
	{
		ProcessInput(key);
		Update();
		Draw();
	}
}

void Game::Shutdown()
{
	Renderer::Get()->Shutdown();

	while (!mActors.empty())
		delete mActors.back();
}

void Game::ProcessInput(unsigned char key)
{
	if (key == 0)
		return;
	else if (key == 27)
		mShouldClose = true;
	else if (key == 'c' || key == 'C')
	{
		ChangeDrawings();
	}
	
	for (auto actor : mActors)
		actor->ProcessInput(key);
}

void Game::Update()
{
	std::vector<Actor*> deads;
	mIsUpdating = true;
	for (auto actor : mActors)
	{
		actor->Update();
		if (actor->GetState() == Actor::State::kDead)
			deads.emplace_back(actor);
	}
	mIsUpdating = false;

	for (auto pending : mPendingActors)
	{
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	for (auto actor : deads)
	{
		delete actor;
	}
}

void Game::Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mMeshShader->SetActive();
	for (auto actor : mActors)
		actor->Draw(mMeshShader);

	glutSwapBuffers();
}

void Game::AddActor(Actor* actor)
{
	if (mIsUpdating)
		mPendingActors.emplace_back(actor);
	else
		mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(std::begin(mPendingActors), std::end(mPendingActors), actor);
	if (iter != std::end(mPendingActors))
		mPendingActors.erase(iter);

	iter = std::find(std::begin(mActors), std::end(mActors), actor);
	if (iter != std::end(mActors))
		mActors.erase(iter);
}

void Game::GenerateCube()
{
	new Plane{ this, Plane::Type::kTop };
	new Plane{ this, Plane::Type::kBottom };
	new Plane{ this, Plane::Type::kLeft };
	new Plane{ this, Plane::Type::kRight };
	new Plane{ this, Plane::Type::kFront };
	new Plane{ this, Plane::Type::kBack };
}

void Game::GeneratePyramid()
{
	new Pyramid{ this, Pyramid::Type::kBottom };
	new Pyramid{ this, Pyramid::Type::kLeft};
	new Pyramid{ this, Pyramid::Type::kRight};
	new Pyramid{ this, Pyramid::Type::kFront};
	new Pyramid{ this, Pyramid::Type::kBack};
}

void Game::ChangeDrawings()
{
	if (mIsCube)
	{
		for (auto actor : mActors)
			actor->SetState(Actor::State::kDead);

		GeneratePyramid();
	}
	else
	{
		for (auto actor : mActors)
			actor->SetState(Actor::State::kDead);
		GenerateCube();
	}
	mIsCube = !mIsCube;
}