// -----------------------------------
// 실습 2번
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
void changeColor(int button, int state, int x, int y);

bool shouldBGColorChange = true;
bool shouldRectColorChange = true;

glm::vec3 bgColor(0.0f, 0.0f, 0.0f);
glm::vec3 rectColor(0.0f, 0.0f, 0.0f);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
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
	glutMouseFunc(changeColor);
	glutMainLoop();

	return 0;
}


void drawScene()
{
	if (shouldBGColorChange)
	{
		shouldBGColorChange = false;
		bgColor = glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat());
	}
	glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw a rect
	if (shouldRectColorChange)
	{
		shouldRectColorChange = false;
		rectColor = glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat());
	}
	glColor3f(rectColor.x, rectColor.y, rectColor.z);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

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
	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;
	}
}

void changeColor(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glm::vec2 ndc = screenToNDC(x, y);
		//std::cout << ndc.x << ", " << ndc.y << std::endl;
		if (-0.5f <= ndc.x && ndc.x <= 0.5f && -0.5f <= ndc.y && ndc.y <= 0.5f)
			shouldRectColorChange = true;
		else
			shouldBGColorChange = true;
	}
	glutPostRedisplay();
}