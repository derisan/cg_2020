// -----------------------------------
// �ǽ�12. �������� �̿��Ͽ� 3���� ��ü �׸���
// 2016180007 ����
// -----------------------------------

#include <vector>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "random.h"
#include "shader.h"
#include "cube.h"
#include "pyramid.h"


// Callback functions
void Draw();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void ArrowKey(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void LoadData();
void UnloadData();
void Move(int key);
void Reset();

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
Shader* spriteShader{ nullptr };

// Objects need to draw
std::vector<Object*> objs;
Object* curObj{ nullptr };

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

	// Object update & drawing
	curObj->Update(dt);
	curObj->Draw(shader);

	// Draw x, y coordinate line
	spriteShader->SetActive();
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.0f, -1.0f);
	glEnd();
	

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
		// ���� ����
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
		// x�� ȸ��
		case 'x': case 'X':
			curObj->SetState(Object::State::kActive);
			curObj->SetAxis(glm::vec3{ 1.0f, 0.0f, 0.0f });
			break;
		// y�� ȸ��
		case 'y': case 'Y':
			curObj->SetState(Object::State::kActive);
			curObj->SetAxis(glm::vec3{ 0.0f, 1.0f, 0.0f });
			break;
		// ���߱�, ��ġ �ʱ�ȭ
		case 's': case 'S':
			Reset();
			break;
		// �׸��� ���
		case 'w': case 'W':
			isWireframe = !isWireframe;
			if (isWireframe)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		// ������ü
		case 'c': case 'C':
			if (curObj && curObj != objs[0])
			{
				curObj->SetState(Object::State::kPaused);
				curObj = objs[0];
			}
			break;
		// �簢��
		case 'p': case 'P':
			if (curObj && curObj != objs[1])
			{
				curObj->SetState(Object::State::kPaused);
				curObj = objs[1];
			}
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
			Move(key);
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

	spriteShader = new Shader();
	spriteShader->Load("Shaders/sprite.vert", "Shaders/sprite.frag");

	objs.emplace_back(new Cube());
	objs.emplace_back(new Pyramid());
	curObj = objs[0];

	camera.position = glm::vec3{ 0.0f, 0.0f, 3.0f };
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

void Move(int key)
{
	glm::vec3 pos{ 0.0f };

	switch (key)
	{
		case GLUT_KEY_UP:
			pos = curObj->GetPosition() + glm::vec3{ 0.0f, 0.1f, 0.0f };
			break;
		case GLUT_KEY_DOWN:
			pos = curObj->GetPosition() + glm::vec3{ 0.0f, -0.1f, 0.0f };
			break;
		case GLUT_KEY_LEFT:
			pos = curObj->GetPosition() + glm::vec3{ -0.1f, 0.0f, 0.0f };
			break;
		case GLUT_KEY_RIGHT:
			pos = curObj->GetPosition() + glm::vec3{ 0.1f, 0.0f, 0.0f };
			break;
	}
	curObj->SetPosition(pos);
}

void Reset()
{
	curObj->SetState(Object::State::kPaused);
	curObj->SetRotation(30.0f);
	curObj->SetAxis(glm::vec3{ 1.0f, 1.0f, 0.0f });
	curObj->SetPosition(glm::vec3{ 0.0f, 0.0f, 0.0f });
}