// -----------------------------------
// 실습 3번
// 2016180007 김명규
// -----------------------------------

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include "utils.h"

class Rect
{
public:
	Rect(float x, float y);

	void draw();
	void update(float dt);

private:
	glm::vec2 _pos;
	glm::vec3 _color;
	glm::vec2 _dir;
	float _scale;
	float _speed;
};

Rect::Rect(float x, float y)
	: _pos(x, y),
	_color(Random::getFloat(), Random::getFloat(), Random::getFloat()),
	_dir(1, 1),
	_scale(1.0f),
	_speed(0.05f)
{
}

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

const float rectLen = 0.1f;
const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;

std::vector<Rect*> rects;

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

	std::vector<Rect*> rects;
	rects.reserve(sizeof(Rect*) * 10);

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

	for (auto rect : rects)
		rect->draw();

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
		for (auto rect : rects)
			delete rect;
		rects.clear();
		glutLeaveMainLoop();
		break;
	}
}

void getRectPos(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glm::vec2 pos = screenToNDC(x, y, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT));
		//shouldRectColorChange = true;
		rects.emplace_back(new Rect(pos.x, pos.y));
	}
}

void playAnimation(int value)
{
	if (shouldAnimPlay)
	{
		for (auto rect : rects)
			rect->update(FPS / 1000);

		glutTimerFunc(static_cast<unsigned int>(1000 / FPS), playAnimation, 1);
	}
	glutPostRedisplay();
}

void Rect::draw()
{
	glColor3f(_color.x, _color.y, _color.z);
	glRectf(_pos.x - (rectLen * _scale), _pos.y - (rectLen * _scale), _pos.x + (rectLen * _scale), _pos.y + (rectLen * _scale));
}

void Rect::update(float dt)
{
	float border = 1.0f - rectLen;

	if (_scale > 2.0f)
		_scale -= sin(dt);
	else if ( _scale < -2.0f)
		_scale += sin(dt);

	std::cout << _scale << std::endl;

	glm::vec2 pos = _pos;
	pos.x += _dir.x * _speed;
	pos.y += _dir.y * _speed;

	_pos = pos;

	if (_pos.x > border || _pos.x < -border)
		_dir.x *= -1;
	if (_pos.y > border || _pos.y < -border)
		_dir.y *= -1;
}