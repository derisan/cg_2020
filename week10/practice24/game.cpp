#include "game.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include "random.h"
#include "renderer.h"
#include "shader.h"
#include "background.h"
#include "snowman.h"
#include "snow.h"
#include "cube.h"

Game::Game()
	: mRenderer{ nullptr },
	mPhongShader{ nullptr },
	mScrWidth{ 0 },
	mScrHeight{ 0 },
	mShouldClose{ false },
	mIsUpdating{ false },
	mIsSnowy{ true },
	mCameraPos{ 0.0f, 5.0f, 2.0f }
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
	glutCreateWindow("Practice 24");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize GLEW" << std::endl;
		return false;
	}

	Random::Init();

	mRenderer = Renderer::Get();
	mPhongShader = mRenderer->GetShader("phong");
	mPhongShader->SetActive();
	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(mScrWidth) / mScrHeight, 0.1f, 100.0f);
	mPhongShader->SetMatrix4Uniform("uProj", proj);

	new Background{ this };
	new Snowman{ this };
	GenerateCubes();
	
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
	else if (key == 'z')
		mCameraPos.y -= 0.1f;
	else if (key == 'x')
		mCameraPos.y += 0.1f;
	else if (key == 's')
		mIsSnowy = !mIsSnowy;
	
	for (auto actor : mActors)
		actor->ProcessInput(key);
}

void Game::Update()
{
	if(mIsSnowy)
		GenerateSnows();

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
		RemoveSnow(actor);
		delete actor;
	}
}

void Game::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	mPhongShader->SetActive();
	SetLightingUniforms();
	for (auto actor : mActors)
		actor->Draw(mPhongShader);

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

void Game::SetLightingUniforms()
{
	glm::mat4 view{ 1.0f };
	view = glm::lookAt(mCameraPos, glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
	mPhongShader->SetMatrix4Uniform("uView", view);
	mPhongShader->SetVectorUniform("uViewPos", mCameraPos);
	mPhongShader->SetVectorUniform("uDirLight.direction", glm::vec3{ -12.0f, -8.0f, -0.1f });
	mPhongShader->SetVectorUniform("uDirLight.ambient", glm::vec3{ 0.1f });
	mPhongShader->SetVectorUniform("uDirLight.diffuse", glm::vec3{ 1.0f });
	mPhongShader->SetVectorUniform("uDirLight.specular", glm::vec3{ 1.0f });
}

void Game::GenerateSnows()
{
	if (mSnows.size() < 40)
		new Snow{ this };
}

void Game::RemoveSnow(Actor* actor)
{
	auto iter = std::find(std::begin(mSnows), std::end(mSnows), actor);
	if (iter != std::end(mSnows))
		mSnows.erase(iter);
}

void Game::GenerateCubes()
{
	auto cube = new Cube{ this };
	cube->SetPosition(glm::vec3{ -2.0f, -0.88f, -0.1f });

	cube = new Cube{ this };
	cube->SetPosition(glm::vec3{ -2.0f, -0.88f, -0.5f });

	cube = new Cube{ this };
	cube->SetPosition(glm::vec3{ -2.0f, -0.88f, -0.9f });

	cube = new Cube{ this };
	cube->SetPosition(glm::vec3{ 0.0f, -0.88f, -0.1f });

	cube = new Cube{ this };
	cube->SetPosition(glm::vec3{ 0.0f, -0.88f, -0.5f });

	cube = new Cube{ this };
	cube->SetPosition(glm::vec3{ 0.0f, -0.88f, -0.9f });
}