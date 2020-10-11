// -----------------------------------
// 실습12. 꼭지점을 이용하여 3차원 객체 그리기
// 2016180007 김명규
// -----------------------------------

#include <vector>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "random.h"
#include "cube.h"
#include "shader.h"


// Callback functions
void Draw();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void ArrowKey(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void LoadData();

struct Camera
{
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};

Camera camera;

const int kScrWidth{ 800 };
const int kScrHeight{ 600 };

Shader* shader{ nullptr };

std::vector<Object*> objs;

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
	
	shader->SetActive();

	glm::mat4 view = glm::lookAt(camera.position, camera.target, camera.up);
	glm::mat4 proj = glm::perspective(glm::radians(45.0f),
		static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight),
		0.1f,
		100.0f);

	shader->SetMatrixUniform("uView", view);
	shader->SetMatrixUniform("uProj", proj);

	float dt = 16.0f / 1000.0f;

	// Update
	for (auto obj : objs)
		obj->Update(dt);
	
	// Draw
	for (auto obj : objs)
		obj->Draw(shader);

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
		case 'q': case 'Q':
			glutLeaveMainLoop();
			break;
	}
}

void ArrowKey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			break;
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
	shader->Load("Shaders/basic.vert", "Shaders/basic.frag");
	
	Cube* cube = new Cube();
	objs.emplace_back(cube);

	camera.position = glm::vec3{ 0.0f, 0.0f, 3.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };
}