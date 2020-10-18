// -----------------------------------
// ½Ç½À15
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "shader.h"
#include "sun.h"

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
constexpr int kScrHeight{ 600 };
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

Sun* sun{ nullptr };
Shader* meshShader{ nullptr };

auto drawMode = GL_FILL;

int main(int argc, char** argv)
{
	bool success = Init(kScrWidth, kScrHeight, &argc, argv);
	if (success == false)
		return -1;
	
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

	sun->Update(dt);
	sun->Draw(meshShader);

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
			break;
		case 'x': case 'X':
			break;
		case 'y': case 'Y':
			break;
		case 'w': case 'W':
		case 's': case 'S':
		case 'a': case 'A':
		case 'd': case 'D':
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
	camera.position = glm::vec3{ 0.0f, 0.0f, 3.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	meshShader = new Shader();
	if (!meshShader->Load("Shaders/mesh.vert", "Shaders/mesh.frag"))
	{
		std::cout << "Failed to load Shaders" << std::endl;
		return;
	}

	meshShader->SetActive();
	glm::mat4 view{ 1.0f };
	view = glm::lookAt(camera.position, camera.target, camera.up);
	meshShader->SetMatrixUniform("uView", view);

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	meshShader->SetMatrixUniform("uProj", proj);
	sun = new Sun();
	sun->SetScale(0.3f);
}

void ChangeDrawStyle()
{
	if (drawMode == GL_LINE)
		drawMode = GL_FILL;
	else
		drawMode = GL_LINE;
		
	glPolygonMode(GL_FRONT_AND_BACK, drawMode);
}