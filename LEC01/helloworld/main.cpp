// -----------------------------------
// 실습 1번
// 2016180007 김명규
// -----------------------------------

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include "utils.h"

void drawScene();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void changeBGColor(int value);

glm::vec3 color(1.0f, 1.0f, 1.0f);
bool shouldTimerStop = false;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutCreateWindow("Example1");

	Random::init();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialization" << std::endl;

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}

void drawScene()
{
	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r': case 'R':
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 'g': case 'G':
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case 'b': case 'B':
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	case 'a': case 'A':
		color = glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat());
		break;
	case 'w': case 'W':
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	case 'k': case 'K':
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		break;
	case 't': case 'T':
		shouldTimerStop = false;
		glutTimerFunc(1000, changeBGColor, 1);
		break;
	case 's': case 'S':
		shouldTimerStop = true;
		break;
	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

void changeBGColor(int value)
{
	if (!shouldTimerStop)
	{
		color = glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat());
		glutTimerFunc(1000, changeBGColor, 1);
	}
	glutPostRedisplay();
}