// -----------------------------------
// ½Ç½À 25
// 2020. 11. 08
// Code by derisan (derisan@naver.com)
// -----------------------------------

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "game.h"

void DisplayFunc();
void ReshapeFunc(int w, int h);
void KeyboardFunc(unsigned char i, int x, int y);
void TimerFunc(int value);
void Shutdown();

Game game;

int main(int argc, char** argv)
{
	if (!game.Init(&argc, argv, 1024, 768))
	{
		std::cout << "Failed to initialize game" << std::endl;
		return -1;
	}

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
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

unsigned char key;
void KeyboardFunc(unsigned char i, int x, int y)
{
	key = i;
}

void TimerFunc(int value)
{
	glutTimerFunc(16, TimerFunc, 1);
	game.Run(key);
	if (game.GetShouldClose())
		Shutdown();
	key = NULL;
}

void Shutdown()
{
	game.Shutdown();
	glutLeaveMainLoop();
}