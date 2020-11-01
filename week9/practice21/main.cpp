// -----------------------------------
// ½Ç½À20
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "cube.h"
#include "plane.h"
#include "shader.h"

void DisplayFunc();
void ReshapeFunc(int w, int h);
void KeyboardFunc(unsigned char key, int x, int y);
void TimerFunc(int value);
void UpdateFunc();

bool LoadData();
void Shutdown();

void ChangeLightColor(int option);
void ChangeLightTurn();
void MoveCrane(unsigned int key);

constexpr int kScrWidth{ 1024 };
constexpr int kScrHeight{ 768 };
constexpr float dt{ 16.0f / 1000.0f };

struct Camera
{
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};

std::vector<Object*> objs;
Cube* lightCube{ nullptr };
Shader* meshShader{ nullptr };
Shader* phongShader{ nullptr };
Camera camera;
glm::vec3 lightColor{ 1.0f };
int lightColorOption{ 0 };
float lightRotateAngle{ 0.0f };
bool shouldLightRotate{ false };
float cameraRotateAngle{ 0.0f };
bool shouldCameraRotate{ false };
bool shouldTurnoffLight{ false };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(kScrWidth, kScrHeight);
	glutCreateWindow("Practice 21");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Unable to initialize GLEW" << std::endl;
		return -1;
	}
	else
		std::cout << "GLEW Initialization" << std::endl;

	if (!LoadData())
	{
		std::cout << "Failed to load data" << std::endl;
		return -1;
	}

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutTimerFunc(16, TimerFunc, 1);
	glutMainLoop();

	return 0;
}

void UpdateFunc()
{
	for (auto obj : objs)
		obj->Update();

	lightCube->Update();
}

void DisplayFunc()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	if (shouldLightRotate)
		lightRotateAngle += cos(dt);
	if (shouldCameraRotate)
		cameraRotateAngle += cos(dt);

	meshShader->SetActive();
	glm::mat4 view{ 1.0f };
	view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);

	glm::mat4 out{ 1.0f };
	out = glm::rotate(out, glm::radians(lightRotateAngle + cameraRotateAngle), glm::vec3{ 0.0f, 1.0f, 0.0f });
	meshShader->SetMatrix4Uniform("uView", view);
	meshShader->SetMatrix4Uniform("uProj", proj);
	meshShader->SetMatrix4Uniform("uOut", out);
	lightCube->Draw(meshShader);

	phongShader->SetActive();
	phongShader->SetVectorUniform("lightPos", glm::vec3(out * glm::vec4(lightCube->GetPosition(), 1.0f)));
	phongShader->SetMatrix4Uniform("uView", view);
	phongShader->SetMatrix4Uniform("uProj", proj);
	phongShader->SetVectorUniform("viewPos", camera.position);
	phongShader->SetVectorUniform("lightColor", lightColor);
	out = glm::mat4{ 1.0f };
	out = glm::rotate(out, glm::radians(cameraRotateAngle), glm::vec3{ 0.0f, 1.0f, 0.0f });
	phongShader->SetMatrix4Uniform("uOut", out);
	
	for (auto obj : objs)
		obj->Draw(phongShader);

	glutSwapBuffers();
}

void ReshapeFunc(int w, int h)
{
	glViewport(0, 0, w, h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			Shutdown();
		case 'c': case 'C':
			lightColorOption = (lightColorOption + 1) % 4;
			ChangeLightColor(lightColorOption);
			break;
		case 'r': case 'R':
			shouldLightRotate = !shouldLightRotate;
			break;
		case 'y': case 'Y':
			shouldCameraRotate = !shouldCameraRotate;
			break;
		case 'm': case 'M':
			shouldTurnoffLight = !shouldTurnoffLight;
			ChangeLightTurn();
			break;
		case 'w': case 'W':
		case 's': case 'S':
		case 'a': case 'A':
		case 'd': case 'D':
			MoveCrane(key);
			break;
		case 'z': case 'Z':
			camera.position.z += 0.1f;
			break;
		case 'x': case 'X':
			camera.position.z -= 0.1f;
			break;
	}
}


void TimerFunc(int value)
{
	glutTimerFunc(16, TimerFunc, 1);	
	UpdateFunc();
	glutPostRedisplay();
}

void Shutdown()
{
	for (auto obj : objs)
		delete obj;
	
	delete lightCube;
	delete meshShader;
	delete phongShader;
	glutLeaveMainLoop();
}

bool LoadData()
{
	meshShader = new Shader{};
	phongShader = new Shader{};
	if (!meshShader->Load("Shaders/mesh.vert", "Shaders/mesh.frag") ||
		!phongShader->Load("Shaders/phong.vert", "Shaders/phong.frag"))
	{
		std::cout << "Failed to load shaders" << std::endl;
		return false;
	}

	camera.position = glm::vec3{ 0.0f, 1.0f, 6.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	Cube* cube = new Cube{};
	cube->SetColor(glm::vec3{ 1.0f, 0.0f, 0.0f });
	cube->SetScale(glm::vec3{ 1.0f, 0.5f, 1.0f });
	objs.emplace_back(cube);

	cube = new Cube{};
	cube->SetColor(glm::vec3{ 0.0f, 1.0f, 0.0f });
	cube->SetScale(glm::vec3{ 0.5f, 0.25f, 0.5f });
	cube->SetPosition(glm::vec3{ 0.0f, 0.25f, 0.0f });
	objs.emplace_back(cube);

	cube = new Cube{};
	cube->SetColor(glm::vec3{ 0.0f, 0.0f, 1.0f });
	cube->SetScale(glm::vec3{ 0.1f, 0.5f, 0.1f });
	cube->SetPosition(glm::vec3{ -0.1f, 0.5f, 0.0f });
	objs.emplace_back(cube);

	cube = new Cube{};
	cube->SetColor(glm::vec3{ 0.0f, 0.0f, 1.0f });
	cube->SetScale(glm::vec3{ 0.1f, 0.5f, 0.1f });
	cube->SetPosition(glm::vec3{ 0.1f, 0.5f, 0.0f });
	objs.emplace_back(cube);

	Plane* plane = new Plane{};
	plane->SetColor(glm::vec3{ 0.4f, 0.2f, 0.1f });
	plane->SetScale(glm::vec3{ 5.0f, 1.0f, 5.0f });
	plane->SetPosition(glm::vec3{ 0.0f, -0.25f, 0.0f });
	objs.emplace_back(plane);
	
	lightCube = new Cube{};
	lightCube->SetScale(glm::vec3{ 0.2f, 0.2f, 0.2f });
	lightCube->SetPosition(glm::vec3{ 0.0f, 0.0f, 3.0f });

	std::cout << "Asdf" << std::endl;

	return true;
}

void ChangeLightColor(int option)
{
	switch (option)
	{
		case 0:
			lightColor = glm::vec3{ 1.0f, 1.0f, 1.0f };
			break;
		case 1:
			lightColor = glm::vec3{ 1.0f, 1.0f, 0.0f };
			break;
		case 2:
			lightColor = glm::vec3{ 0.0f, 1.0f, 1.0f };
			break;
		case 3:
			lightColor = glm::vec3{ 1.0f, 0.0f, 1.0f };
			break;
		case 4:
			lightColor = glm::vec3{ 0.0f, 0.0f, 0.0f };
			break;
	}
}

void ChangeLightTurn()
{
	if (shouldTurnoffLight)
		ChangeLightColor(4);
	else
		ChangeLightColor(lightColorOption);
}

void MoveCrane(unsigned int key)
{
	float forwardSpeed{ 0.0f };
	float strafeSpeed{ 0.0f };

	switch (key)
	{
		case 'w': case 'W':
			forwardSpeed -= 0.1f;
			break;
		case 's': case 'S':
			forwardSpeed += 0.1f;
			break;
		case 'a': case 'A':
			strafeSpeed -= 0.1f;
			break;
		case 'd': case 'D':
			strafeSpeed += 0.1f;
			break;
	}

	for (int i = 0; i < 4; ++i)
	{
		auto pos = objs[i]->GetPosition();
		pos.z += forwardSpeed;
		pos.x += strafeSpeed;
		objs[i]->SetPosition(pos);
	}
}