#include "game.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "random.h"
#include "shader.h"
#include "line.h"
#include "object_manager.h"
#include "utils.h"

Game::Game(int w, int h)
	: mScrWidth{ w },
	mScrHeight{ h },
	mShader{ nullptr },
	mCutter{ nullptr },
	mCutterStartPos{ 0.0f, 0.0f },
	mCutterEndPos{ 0.0f, 0.0f },
	mObjManager{ nullptr },
	mDrawMode{ GL_LINE },
	mShouldPause{ false }
{
	
}

Game::~Game()
{

}

bool Game::Init(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
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
}

void Game::Shutdown()
{
	delete mShader;
	delete mCutter;
	delete mObjManager;
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
}


void Game::Update()
{
	if (mShouldPause)
		return;

	mObjManager->Update();
	mObjManager->CollisionCheck(mCutter);
}


void Game::Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, mDrawMode);

	mShader->SetActive();

	mObjManager->Draw();
	
	if (mCutter)
		mCutter->Draw();
	
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