// -----------------------------------
// ½Ç½À22
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "sphere.h"
#include "shader.h"
#include "plane.h"
#include "random.h"

void DisplayFunc();
void ReshapeFunc(int w, int h);
void KeyboardFunc(unsigned char key, int x, int y);
void TimerFunc(int value);
void UpdateFunc();

bool LoadData();
void Shutdown();

void ChangeLightColor(int option);

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
Sphere* lightCube{ nullptr };
Shader* meshShader{ nullptr };
Shader* phongShader{ nullptr };
Camera camera;
glm::vec3 lightColor{ 1.0f };
int lightColorOption{ 0 };
float lightRotateAngle{ 0 };
bool shouldRotate{ false };

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(kScrWidth, kScrHeight);
	glutCreateWindow("Practice 22");

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
	
	Random::Init();

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	meshShader->SetActive();

	glm::mat4 view{ 1.0f };
	view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	glm::mat4 out{ 1.0f };
	if (shouldRotate)
		lightRotateAngle += cos(dt);
	
	out = glm::rotate(out, glm::radians(lightRotateAngle), glm::vec3{ 0.0f, 0.0f, 1.0f });
	meshShader->SetMatrix4Uniform("uView", view);
	meshShader->SetMatrix4Uniform("uProj", proj);
	meshShader->SetMatrix4Uniform("uOut", out);
	
	lightCube->Draw(meshShader);

	phongShader->SetActive();
	phongShader->SetMatrix4Uniform("uView", view);
	phongShader->SetMatrix4Uniform("uProj", proj);
	phongShader->SetVectorUniform("lightPos", glm::vec3( glm::rotate(lightCube->GetPosition(), glm::radians(lightRotateAngle),
		glm::vec3{ 0.0f, 0.0f, 1.0f })));
	phongShader->SetVectorUniform("viewPos", camera.position);
	phongShader->SetVectorUniform("lightColor", lightColor);
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
			shouldRotate = !shouldRotate;
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

	camera.position = glm::vec3{ 0.0f, 0.5f, 15.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	auto sphere = new Sphere{};
	sphere->SetColor(glm::vec3{ 1.0f, 0.0f, 0.0f });
	sphere->SetScale(0.6f);
	sphere->SetPosition(glm::vec3{ -1.0f, 0.0f, 0.0f });
	sphere->SetIsPlanet(true);
	objs.emplace_back(sphere);

	sphere = new Sphere{};
	sphere->SetColor(glm::vec3{ 0.0f, 1.0f, 0.0f });
	sphere->SetScale(0.4f);
	sphere->SetPosition(glm::vec3{ -2.0f, 0.0f, 0.0f });
	sphere->SetIsPlanet(true);
	objs.emplace_back(sphere);

	sphere = new Sphere{};
	sphere->SetColor(glm::vec3{ 0.0f, 0.0f, 1.0f });
	sphere->SetScale(0.2f);
	sphere->SetPosition(glm::vec3{ -3.0f, 0.0f, 0.0f });
	sphere->SetIsPlanet(true);
	objs.emplace_back(sphere);

	sphere = new Sphere{};
	sphere->SetColor(glm::vec3{ 0.68f, 0.36f, 0.1f });
	sphere->SetPosition(glm::vec3{ 0.0f, -1.0f, 0.0f });
	objs.emplace_back(sphere);

	lightCube = new Sphere{};
	lightCube->SetScale(0.2f);
	lightCube->SetPosition(glm::vec3{ -7.0f, 0.0f, 0.0f });

	auto plane = new Plane{};
	plane->SetScale(10.0f);
	plane->SetPosition(glm::vec3{ 0.0f, -2.0f, 0.0f });
	objs.emplace_back(plane);

	for (int i = 0; i < 100; ++i)
	{
		sphere = new Sphere{};
		sphere->SetColor(glm::vec3{ 0.3f, 0.3f, 0.3f });
		sphere->SetScale(0.1f);
		sphere->SetPosition(glm::vec3{ Random::GetFloatRange(-3.0f, 3.0f), 2.0f, Random::GetFloatRange(-3.0f, 3.0f) });
		sphere->SetIsSnow(true);
		sphere->SetSpeed(Random::GetFloatRange(0.01f, 0.1f));
		objs.emplace_back(sphere);
	}


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
	}
}