// -----------------------------------
// camera_work
// main.cpp
// 2020. 11. 16
// Code by derisan (derisan@naver.com)
// -----------------------------------

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "gfw.h"

void DisplayFunc();
void ReshapeFunc(int w, int h);
void KeyboardFunc(unsigned char key, int x, int y);
void KeyboardUpFunc(unsigned char key, int x, int y);
void PassiveMotionFunc(int x, int y);
void TimerFunc(int value);
void Shutdown();

Gfw gfw;

int main(int argc, char** argv)
{
	if (!gfw.Init(&argc, argv, 1024, 768))
	{
		std::cout << "Failed to initialize gfw" << std::endl;
		return -1;
	}

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);
	glutTimerFunc(16, TimerFunc, 1);

	glutMainLoop();

	return 0;
}

void DisplayFunc()
{

}

void ReshapeFunc(int w, int h)
{
	glViewport(0, 0, w, h);
}

bool buffer[256];
void KeyboardFunc(unsigned char key, int x, int y)
{
	buffer[key] = true;
}

void KeyboardUpFunc(unsigned char key, int x, int y)
{
	buffer[key] = false;
}

int prevMouseX, prevMouseY;
int mouseX, mouseY;
bool firstMouse{ true };
void PassiveMotionFunc(int x, int y)
{
	if (firstMouse)
	{
		prevMouseX = 512;
		prevMouseY = 384;
		firstMouse = false;
	}

	mouseX = x - prevMouseX;
	mouseY = prevMouseY - y;

	prevMouseX = x;
	prevMouseY = y;
}

void TimerFunc(int value)
{
	glutTimerFunc(16, TimerFunc, 1);
	gfw.Run(buffer, mouseX, mouseY);
	if (gfw.GetShouldClose())
		Shutdown();

	mouseX = 0;
	mouseY = 0;
}

void Shutdown()
{
	gfw.Shutdown();
	glutLeaveMainLoop();
}