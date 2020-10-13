// -----------------------------------
// �ǽ�13. �پ��� ���
// 2016180007 ����
// -----------------------------------

#include <vector>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "random.h"
#include "shader.h"
#include "cube.h"

// Callback functions
void Draw();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void ArrowKey(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);

// Program specific functions
void LoadData();
void UnloadData();
void Reset();
void DrawAxis();
void DrawSinGraph();

// Settings
const int kScrWidth{ 800 };
const int kScrHeight{ 600 };

// Shader
Shader* shader{ nullptr };

// Program specific globals
bool isRotate{ false };
bool isTravel{ false };
bool isScale{ false };
float angle{ 0.0f };
float dt{ 16.0f / 1000.0f };

Cube* cube{ nullptr };

int main(int argc, char** argv)
{
	bool success = Init(kScrWidth, kScrHeight, &argc, argv);
	if (!success)
		exit(EXIT_FAILURE);
	Random::Init();
	
	LoadData();

	glutDisplayFunc(Draw);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutSpecialFunc(ArrowKey);
	glutTimerFunc(16, Timer, 1);

	glutMainLoop();
	return 0;
}

void Draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Draw x, y coordinate line
	shader->SetActive();
	glm::mat4 world{ 1.0f };
	shader->SetMatrixUniform("uWorld", world);
	DrawAxis();
	
	if (isRotate)
		angle += cos(dt);
	
	world = glm::rotate(world, glm::radians(angle), glm::vec3{ 0.0f, 1.0f, 0.0f });
	shader->SetMatrixUniform("uWorld", world);
	DrawSinGraph();

	cube->Update(dt);
	cube->Draw(shader);

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// ����
		case 'q': case 'Q':
			UnloadData();
			glutLeaveMainLoop();
			break;
		case 't': case 'T':
			isTravel = !isTravel;
			cube->SetShouldTravel(isTravel);
			break;
		case 's': case 'S':
			isScale = !isScale;
			cube->SetShouldScale(isScale);
			break;
		case 'r': case 'R':
			isRotate = !isRotate;
			cube->SetShouldRotate(isRotate);
			break;
		case 'c': case 'C':
			Reset();
			break;
	}
}

void ArrowKey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	glutPostRedisplay();
}

void Timer(int value)
{
	glutTimerFunc(16, Timer, 1);
	glutPostRedisplay();
}

void LoadData()
{
	shader = new Shader();
	shader->Load("Shaders/sprite.vert", "Shaders/sprite.frag");

	cube = new Cube();
}

void UnloadData()
{
	delete cube;
}


void Reset()
{
	isTravel = false;
	isRotate = false;
	isScale = false;
	angle = 0.0f;
	cube->Reset();
}

void DrawAxis()
{
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
}

void DrawSinGraph()
{
	glBegin(GL_LINE_STRIP);
	for (int i = -200; i < 200; i += 3)
		glVertex3f(0.005 * i, sin(glm::radians((float)i)), 0.0f);
	glEnd();
}