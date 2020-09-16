// -----------------------------------
// 실습 3번
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
void getRectPos(int button, int state, int x, int y);
void playAnimation(int value);

glm::vec2 rectPos(0.0f, 0.0f);
glm::vec3 bgColor(0.17f, 0.17f, 0.17f);
glm::vec3 rectColor(0.0f, 0.0f, 0.0f);

bool shouldAnimPlay = false;
bool shouldRectColorChange = true;

float FPS = 60.0f;
float rectSpeed = 0.6f / FPS;
int xDir = 1;
int yDir = 1;

const float rectLen = 0.1f;
const int SCR_WIDTH = 600;
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
	glutMouseFunc(getRectPos);
	glutMainLoop();

	return 0;
}

void drawScene()
{
	glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (shouldRectColorChange)
	{
		shouldRectColorChange = false;
		rectColor = glm::vec3(Random::getFloat(), Random::getFloat(), Random::getFloat());
	}
	glColor3f(rectColor.x, rectColor.y, rectColor.z);
	glRectf(rectPos.x - rectLen, rectPos.y - rectLen, rectPos.x + rectLen, rectPos.y + rectLen);

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
	case 'a': case 'A':
		if (!shouldAnimPlay)
		{
			shouldAnimPlay = true;
			glutTimerFunc(16, playAnimation, 1);
		}
		break;
	case 's': case 'S':
		shouldAnimPlay = false;
		break;
	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;
	}
}

void getRectPos(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		rectPos = screenToNDC(x, y, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT));
		shouldRectColorChange = true;
	}
}

void playAnimation(int value)
{
	if (shouldAnimPlay)
	{
		float border = 1.0f - rectLen;

		rectPos.x += xDir * rectSpeed;
		rectPos.y += yDir * rectSpeed;

		if (rectPos.x > border || rectPos.x < -border)
			xDir *= -1;
		if (rectPos.y > border || rectPos.y < -border)
			yDir *= -1;

		glutTimerFunc(static_cast<unsigned int>(1000 / FPS), playAnimation, 1);
	}
	glutPostRedisplay();
}