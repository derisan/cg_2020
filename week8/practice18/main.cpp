// -----------------------------------
// 실습18
// 2016180007 김명규
// -----------------------------------

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "utils.h"
#include "shader.h"
#include "axis.h"
#include "stage.h"
#include "robot.h"

// Camera things
struct Camera
{
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};

Camera camera;

// Settings
constexpr int kScrWidth{ 1024 };
constexpr int kScrHeight{ 768 };
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


// Control camera rotations
bool isRotateCameraTarget{ false };
bool isRotateCameraPosition{ false };


float cameraRotateAngle{ 0.0f };

Shader* meshShader{ nullptr };

Axis* axis{ nullptr };
Stage* stage{ nullptr };
Robot* robot{ nullptr };

auto drawMode = GL_FILL;

constexpr float speed{ 1.5f };
float armSpeed{ 1.5f };

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, drawMode);

	// Set view & proj matrix
	meshShader->SetActive();
	glm::mat4 view{ 1.0f };
	// 카메라 자전
	if (isRotateCameraTarget)
		camera.target = glm::rotate(camera.target, glm::radians(speed), glm::vec3{ 0.0f, 1.0f, 0.0f });
	view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
	meshShader->SetMatrixUniform("uView", view);
		
	// 카메라 공전
	if (isRotateCameraPosition)
		cameraRotateAngle += speed;


	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	meshShader->SetMatrixUniform("uProj", proj);

	glm::mat4 out{ 1.0f };
	out = glm::rotate(out, glm::radians(cameraRotateAngle), glm::vec3{ 0.0f, 1.0f, 0.0f });
	meshShader->SetMatrixUniform("uOut", out);

	
	axis->Update(dt);
	stage->Update(dt);
	robot->Update(dt);

	axis->Draw(meshShader);
	stage->Draw(meshShader);
	robot->Draw(meshShader);
	
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
		MoveCamera(key);
		break;
	case 'w': case 'W':
	case 's': case 'S':
	case 'a': case 'A':
	case 'd': case 'D':
		robot->Move(key);
		break;
	// Rotate camera things
	case 'y': case 'Y':
		isRotateCameraTarget = !isRotateCameraTarget;
		break;
	case 'u': case 'U':
		isRotateCameraPosition = !isRotateCameraPosition;
		break;
	// Open stage
	case 'o': case 'O':
		stage->SetShouldOpenFront(true);
		break;
	// Robot jump
	case 'j': case 'J':
		robot->SetShouldJump(true);
		break;
	// Reset things
	case 'i': case 'I':
		robot->Reset();
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
	delete axis;
	delete stage;
	delete robot;

	glutLeaveMainLoop();
}

void LoadData()
{
	// Set cameara elements
	camera.position = glm::vec3{ 0.0f, 0.5f, 6.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	// Create shader
	meshShader = new Shader();
	if (!meshShader->Load("Shaders/mesh.vert", "Shaders/mesh.frag"))
	{
		std::cout << "Failed to load Shaders" << std::endl;
		return;
	}

	// Axis
	axis = new Axis{};
	axis->SetScale(glm::vec3{ 1.0f, 1.0f, 1.0f });
	
	// Stage
	stage = new Stage{};

	// Robot
	robot = new Robot{};
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
	switch (key)
	{
	case 'z': case 'Z':
		camera.position.z += 0.2f;
		break;
	case 'x': case 'X':
		camera.position.z -= 0.2f;
		break;
	}
}
