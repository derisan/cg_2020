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
void UnloadData();

// Camera things
struct Camera
{
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};

Camera camera;

// Settings
const int kScrWidth{ 800 };
const int kScrHeight{ 600 };

// Shader
Shader* shader{ nullptr };

// Objects need to draw
std::vector<Object*> objs;

// Program specific globals
bool isCullface = false;
bool isWireframe = false;

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
	shader->SetMatrixUniform("uView", view);

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
		// 종료
		case 'q': case 'Q':
			UnloadData();
			glutLeaveMainLoop();
			break;
		// 은면 제거
		case 'h': case 'H':
			isCullface = !isCullface;
			if (isCullface) 
			{
				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CW);
			}
			else
			{
				glDisable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
			}
			break;
		// x축 회전
		case 'x': case 'X':
			for (auto obj : objs)
			{
				obj->SetState(Object::State::kActive);
				obj->SetAxis(glm::vec3{ 1.0f, 0.0f, 0.0f });
			}
			break;
		// y축 회전
		case 'y': case 'Y':
			for (auto obj : objs)
			{
				obj->SetState(Object::State::kActive);
				obj->SetAxis(glm::vec3{ 0.0f, 1.0f, 0.0f });
			}
			break;
		// 멈추기
		case 's': case 'S':
			for (auto obj : objs)
			{
				obj->SetState(Object::State::kPaused);
				obj->SetRotation(0.0f);
			}
			break;
		// 그리기 모드
		case 'w': case 'W':
			isWireframe = !isWireframe;
			if (isWireframe)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		// 정육면체
		case 'c': case 'C':
			Cube * cube = new Cube();
			objs.emplace_back(cube);
			break;
		// 사각뿔
		case 'p': case 'P':
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
	shader->Load("Shaders/basic.vert", "Shaders/basic.frag");

	shader->SetActive();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f),
		static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight),
		0.1f,
		100.0f);
	shader->SetMatrixUniform("uProj", proj);

	camera.position = glm::vec3{ 0.0f, 1.0f, 3.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };
}

void UnloadData()
{
	delete shader;

	for (auto obj : objs)
		delete obj;
	objs.clear();
}