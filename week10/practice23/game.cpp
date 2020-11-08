#include "game.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "renderer.h"
#include "actor.h"
#include "shader.h"

Game::Game()
	: mRenderer{ nullptr },
	mMeshShader{ nullptr },
	mScrWidth{ 0 },
	mScrHeight{ 0 },
	mShouldClose{ false },
	mIsUpdating{ false }
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
}

void Game::ProcessInput(unsigned char key)
{
	if (key == 0)
		return;
	else if (key == 27)
		mShouldClose = true;

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

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