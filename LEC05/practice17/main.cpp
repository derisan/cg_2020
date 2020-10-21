// -----------------------------------
// ½Ç½À17
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "utils.h"
#include "shader.h"
#include "cube.h"
#include "plane.h"

// Camera things
struct Camera
{
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};

Camera camera;

// Settings
constexpr int kScrWidth{ 800 };
constexpr int kScrHeight{ 800 };
constexpr float dt{ 16.0f / 1000.0f };

// Callback functions
void DisplayFunc();
void ReshapeFunc(int w, int h);
void KeyboardFunc(unsigned char key, int x, int y);
void TimerFunc(int value);
void Shutdown();
void LoadData();
void ChangeDrawStyle();
void MoveCamera(unsigned char key);


// Program specific
bool isRotateCamera{ false };

Shader* meshShader{ nullptr };

std::vector<Object*> objs;

auto drawMode = GL_FILL;

constexpr float speed{ 1.5f };

int main(int argc, char** argv)
{
	bool success = Init(kScrWidth, kScrHeight, &argc, argv);
	if (success == false)
		return -1;
	Random::Init();
	LoadData();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutTimerFunc(16, TimerFunc, 1);

	glutMainLoop();
	return 0;
}

void DisplayFunc()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, drawMode);

	// Set view & proj matrix
	meshShader->SetActive();
	glm::mat4 view{ 1.0f };

	if (isRotateCamera)
		camera.target = glm::rotate(camera.target, glm::radians(speed), glm::vec3{ 0.0f, 1.0f, 0.0f });

	view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
	meshShader->SetMatrixUniform("uView", view);

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	meshShader->SetMatrixUniform("uProj", proj);

	glm::mat4 out{ 1.0f };
	meshShader->SetMatrixUniform("uOut", out);

	for (auto obj : objs)
		obj->Update(dt);

	for (auto obj : objs)
		obj->Draw(meshShader);


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
		// 27 == Escape key
		case 27:
			Shutdown();
			break;
		case 'm': case 'M':
			ChangeDrawStyle();
			break;
		case 'z': case 'Z':
		case 'x': case 'X':
		case 'w': case 'W':
		case 's': case 'S':
		case 'a': case 'A':
		case 'd': case 'D':
			MoveCamera(key);
			break;
		case 'y': case 'Y':
			isRotateCamera = !isRotateCamera;
			break;
	}
}

void TimerFunc(int value)
{
	glutTimerFunc(16, TimerFunc, 1);
	glutPostRedisplay();
}

void Shutdown()
{
	for (auto obj : objs)
		delete obj;
	
	glutLeaveMainLoop();
}

void LoadData()
{
	// Set cameara elements
	camera.position = glm::vec3{ 0.0f, 0.5f, 5.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	// Create shader
	meshShader = new Shader();
	if (!meshShader->Load("Shaders/mesh.vert", "Shaders/mesh.frag"))
	{
		std::cout << "Failed to load Shaders" << std::endl;
		return;
	}

	Cube* leg{ new Cube{} };
	leg->SetWorldScale(glm::vec3{ 1.0f, 0.5f, 1.0f });
	objs.emplace_back(leg);

	Plane* plane{ new Plane{Plane::kCyan} };
	plane->SetWorldScale(glm::vec3{ 10.0f, 1.0f, 10.0f });
	plane->SetWorldTranslate(glm::vec3{ 0.0f, -0.25f, 0.0f });
	objs.emplace_back(plane);
}

void ChangeDrawStyle()
{
	if (drawMode == GL_LINE)
		drawMode = GL_FILL;
	else
		drawMode = GL_LINE;
}

void MoveCamera(unsigned char key)
{
	glm::vec3 pos{ 0.0f };

	switch (key)
	{
		case 'w': case 'W':
			camera.position.y += 0.2f;
			break;
		case 's': case 'S':
			camera.position.y -= 0.2f;
			break;
		case 'a': case 'A':
			camera.position.x -= 0.2f;
			break;
		case 'd': case 'D':
			camera.position.x += 0.2f;
			break;
		case 'z': case 'Z':
			camera.position.z += 0.2f;
			break;
		case 'x': case 'X':
			camera.position.z -= 0.2f;
			break;
	}
}
