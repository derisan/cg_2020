#include "game.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "random.h"
#include "utils.h"
#include "shader.h"
#include "object_manager.h"
#include "net.h"
#include "line.h"

Game::Game(int w, int h)
	: mScrWidth{ w },
	mScrHeight{ h },
	mShader{ nullptr },
	mCutter{ nullptr },
	mCutterStartPos{ 0.0f, 0.0f },
	mCutterEndPos{ 0.0f, 0.0f },
	mRightMouseStartPos{ -1.0f, -1.0f },
	mRightMouseEndPos{ -1.0f, -1.0f },
	mObjManager{ nullptr },
	mNet{ nullptr },
	mDrawMode{ GL_FILL },
	mShouldPause{ false },
	mShouldEnd{ false }
{
	
}

Game::~Game()
{

}

bool Game::Init(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(mScrWidth, mScrHeight);
	glutCreateWindow("Slice flying polygons");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize GLEW" << std::endl;
		return false;
	}

	// Load shader
	mShader = new Shader{};
	if (!mShader->Load("Shaders/sprite.vert", "Shaders/sprite.frag"))
		return false;
	mShader->SetActive();

	Random::Init();

	LoadData();

	return true;
}

void Game::LoadData()
{
	mObjManager = new ObjectManager{this};
	mNet = new Net{ mScrWidth, mScrHeight, this };
}

void Game::Shutdown()
{
	delete mShader;
	delete mCutter;
	delete mObjManager;
	delete mNet;
}

void Game::ProcessKeyboardInput(unsigned char key)
{
	switch (key)
	{
		case 'm': case 'M':
			ChangeDrawMode();
			break;
		case 'p': case 'P':
			if(mObjManager->GetShouldDrawPath())
				mObjManager->SetShouldDrawPath(false);
			else
				mObjManager->SetShouldDrawPath(true);
			break;
		case 's': case 'S':
			mShouldPause = !mShouldPause;
			break;
		case 49: // Numpad 1
			mObjManager->SpeedUp(0.001f);
			break;
		case 50: // Numpad 2
			mObjManager->SpeedDown(0.001f);
			break;
	}
}

// Create Cutter when left mouse button up
void Game::ProcessMouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mCutterStartPos = ScreenToNDC(x, y,
			static_cast<float>(mScrWidth), static_cast<float>(mScrHeight));
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mCutterEndPos = ScreenToNDC(x, y,
			static_cast<float>(mScrWidth), static_cast<float>(mScrHeight));
		CreateCutter();
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mRightMouseStartPos = ScreenToNDC(x, y,
			static_cast<float>(mScrWidth), static_cast<float>(mScrHeight));
	}
	
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		mRightMouseEndPos = ScreenToNDC(x, y,
			static_cast<float>(mScrWidth), static_cast<float>(mScrHeight));
	}
}


void Game::Update()
{
	if (mShouldPause)
		return;

	mObjManager->Update();
	mObjManager->CheckCollision(mCutter);

	auto obj = mObjManager->CapturesObject(mRightMouseStartPos);
	if (obj)
	{
		if (mRightMouseEndPos.x != -1.0f && mRightMouseEndPos.y != -1.0f)
		{
			mNet->MouseReposition(obj, mRightMouseEndPos);
			mRightMouseEndPos = glm::vec2{ -1.0f, -1.0f };
		}
	}
	
	auto objs = mObjManager->GetObjects();
	mNet->Update(objs);

	if (mNet->IsOver())
	{
		mShouldEnd = true;
	}
}


void Game::Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, mDrawMode);

	mShader->SetActive();

	if (mCutter)
		mCutter->Draw();
	mObjManager->Draw();
	mNet->Draw();
	
	glutSwapBuffers();
}


void Game::CreateCutter()
{
	if (mCutter)
		delete mCutter;

	mCutter = new Line{ mCutterStartPos, mCutterEndPos };
}

void Game::DeleteCutter()
{
	if (mCutter)
	{
		delete mCutter;
		mCutter = nullptr;
	}
}


void Game::ChangeDrawMode()
{
	if (mDrawMode == GL_LINE)
		mDrawMode = GL_FILL;
	else
		mDrawMode = GL_LINE;
}