// -----------------------------------
// ½Ç½À15
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "shader.h"
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

// Program specific
void ChangeDrawStyle();
void MoveObjects(unsigned char key);

Shader* meshShader{ nullptr };

std::vector<Object*> objs;

auto drawMode = GL_FILL;

float angle{ 0.0f };
float frontAngle{ 0.0f };
bool isRotate{ false };

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
	view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
	meshShader->SetMatrixUniform("uView", view);

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	meshShader->SetMatrixUniform("uProj", proj);


	float speed{ 0.5f };
	
	
	if (isRotate)
	{
		angle += cos(dt);
		frontAngle += speed;
		if (frontAngle > 90.0f)
			frontAngle = 90.0f;
	}

	
	glm::mat4 mat{ 1.0f };
	mat = glm::translate(mat, glm::vec3{ 0.0f, 0.0f, 1.0f });
	mat = glm::rotate(mat, glm::radians(frontAngle), glm::vec3{ 1.0f, 0.0f, 0.0f });
	meshShader->SetMatrixUniform("uOut", mat);
	objs[0]->Draw(meshShader);

	mat = glm::mat4{ 1.0f };
	mat = glm::translate(mat, glm::vec3{ 0.0f, 1.0f, 0.0f });
	mat = glm::rotate(mat, glm::radians(angle), glm::vec3{ 1.0f, 0.0f, 0.0f });
	meshShader->SetMatrixUniform("uOut", mat);
	objs[1]->Draw(meshShader);


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
		case 'y': case 'Y':
			isRotate = !isRotate;
			break;
		case 'z': case 'Z':
		case 'x': case 'X':
		case 'w': case 'W':
		case 's': case 'S':
		case 'a': case 'A':
		case 'd': case 'D':
			MoveObjects(key);
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
	glutLeaveMainLoop();
}

void LoadData()
{
	// Set cameara elements
	camera.position = glm::vec3{ 0.0f, 1.0f, 5.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	// Create shader
	meshShader = new Shader();
	if (!meshShader->Load("Shaders/mesh.vert", "Shaders/mesh.frag"))
	{
		std::cout << "Failed to load Shaders" << std::endl;
		return;
	}

	auto plane_front = new Plane{};
	plane_front->SetWorldRotate(270.0f, glm::vec3{ 1.0f, 0.0f, 0.0f });
	objs.emplace_back(plane_front);

	auto plane_top = new Plane{};
	//plane_top->SetWorldTranslate(glm::vec3{ 0.0f, 1.0f, 0.0f });
	objs.emplace_back(plane_top);


}

void ChangeDrawStyle()
{
	if (drawMode == GL_LINE)
		drawMode = GL_FILL;
	else
		drawMode = GL_LINE;
}

void MoveObjects(unsigned char key)
{
	glm::vec3 pos{ 0.0f };

	switch (key)
	{
		case 'w': case 'W':
			camera.position.y += 0.1f;
			break;
		case 's': case 'S':
			camera.position.y -= 0.1f;
			break;
		case 'a': case 'A':
			camera.position.x -= 0.1f;
			break;
		case 'd': case 'D':
			camera.position.x += 0.1f;
			break;
		case 'z': case 'Z':
			camera.position.z += 0.1f;
			break;
		case 'x': case 'X':
			camera.position.z -= 0.1f;
			break;
	}
}
