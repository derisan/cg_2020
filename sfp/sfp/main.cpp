// -----------------------------------
// ¼÷Á¦1. Slice flying polygons
// 2016180007 ±è¸í±Ô
// -----------------------------------


#include <iostream>
#include <vector>
#include <algorithm>

#include "utils.h"
#include "shader.h"

#include "object.h"
#include "triangle.h"
#include "line.h"

void DisplayFunc();
void ReshapeFunc(int w, int h);
void KeyboardFunc(unsigned char key, int x, int y);
void MouseFunc(int button, int state, int x, int y);
void MotionFunc(int x, int y);
void TimerFunc(int value);

void LoadData();
void Shutdown();

// Program specific
void CreateLine();


constexpr int kScrWidth{ 1024 };
constexpr int kScrHeight{ 768 };
constexpr float dt{ 16.0f / 1000.0f };


Shader* shader{ nullptr };
Line* knife{ nullptr };

std::vector<Object*> objs;


int main(int argc, char** argv)
{
	bool success = Init(kScrWidth, kScrHeight, &argc, argv);
	if (success == false)
		return -1;
	Random::Init();
	
	LoadData();


	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutTimerFunc(16, TimerFunc, 1);


	glutMainLoop();
	return 0;
}

void DisplayFunc()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (auto obj : objs)
		obj->Update(dt);

	for (auto obj : objs)
		obj->Draw(shader);

	glutSwapBuffers();
}

void ReshapeFunc(int w, int h)
{
	glViewport(0, 0, w, h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: // Esc
			Shutdown();
			break;
	}
}

void TimerFunc(int value)
{
	glutTimerFunc(16, TimerFunc, 1);
	glutPostRedisplay();
}

void Shutdown()
{
	for (auto obj : objs)
		delete obj;
	objs.clear();

	delete shader;

	glutLeaveMainLoop();
}


glm::vec3 startPos{ 0.0f };
glm::vec3 endPos{ 0.0f };
void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		startPos = glm::vec3{ ScreenToNDC(x, y, kScrWidth, kScrHeight), 0.0f };
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		endPos = glm::vec3{ ScreenToNDC(x, y, kScrWidth, kScrHeight), 0.0f };
		CreateLine();
	}
}

void CreateLine()
{
	if (knife)
	{
		auto iter = std::find(objs.begin(), objs.end(), knife);
		if (iter != objs.end())
		{
			delete (*iter);
			objs.erase(iter);
		}
	}

	knife = new Line{ startPos, endPos };
	objs.emplace_back(knife);
}

void MotionFunc(int x, int y)
{

}

void LoadData()
{
	shader = new Shader{};
	if (!shader->Load("Shaders/sprite.vert", "Shaders/sprite.frag"))
	{
		std::cout << "Failed to load shaders" << std::endl;
		exit(EXIT_FAILURE);
	}

	auto tri{ new Triangle{} };
	objs.emplace_back(tri);
}