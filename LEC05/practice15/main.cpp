// -----------------------------------
// ½Ç½À15
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "shader.h"
#include "cube.h"
#include "orbit.h"

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
void MoveObjects(unsigned char key);

Shader* meshShader{ nullptr };

std::vector<Object*> objs;

auto drawMode = GL_FILL;

float angle{ 0.0f };
float speedOne{ 0.0f };
float speedTwo{ 0.0f };
float speedThree{ 0.0f };
bool isRotate{ true };

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
	view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
	meshShader->SetMatrixUniform("uView", view);

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	meshShader->SetMatrixUniform("uProj", proj);

	if (isRotate)
		angle += cos(dt);

	float speed{ 1.5f };

	glm::mat4 mat{ 1.0f };
	meshShader->SetMatrixUniform("uOut", mat);

	// ÀÚÀü
	objs[0]->SetWorldRotate(1.5f, glm::vec3{ 0.0f, 1.0f, 0.0f });
	objs[0]->Draw(meshShader);

	// 1¹ø ±Ëµµ
	{
		objs[3]->Draw(meshShader);
		// Áö±¸
		mat = glm::rotate(mat, glm::radians(angle * speedOne), 
			glm::vec3{ 0.0f, 1.0f, 0.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[1]->Draw(meshShader);
		objs[4]->Draw(meshShader);

		// ´Þ
		mat = glm::translate(mat, glm::vec3{ -1.0f, 0.0f, 0.0f });
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3{ 0.0f, 1.0f, 0.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[2]->Draw(meshShader);
	}

	// 2¹ø ±Ëµµ
	{
		mat = glm::mat4{ 1.0f };
		mat = glm::rotate(mat, glm::radians(45.0f), glm::vec3{ 0.0f, 0.0f, 1.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[7]->Draw(meshShader);

		mat = glm::rotate(mat, glm::radians(angle * speedTwo), glm::vec3{ 0.0f, 1.0f, 0.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[5]->Draw(meshShader);
		objs[8]->Draw(meshShader);

		mat = glm::translate(mat, glm::vec3{ -1.0f, 0.0f, 0.0f });
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3{ 0.0f, 1.0f, 0.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[6]->Draw(meshShader);
	}

	// 3¹ø ±Ëµµ
	{
		mat = glm::mat4{ 1.0f };
		mat = glm::rotate(mat, glm::radians(-45.0f), glm::vec3{ 0.0f, 0.0f, 1.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[11]->Draw(meshShader);

		mat = glm::rotate(mat, glm::radians(angle * speedThree), glm::vec3{ 0.0f, 1.0f, 0.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[9]->Draw(meshShader);
		objs[12]->Draw(meshShader);

		mat = glm::translate(mat, glm::vec3{ -1.0f, 0.0f, 0.0f });
		mat = glm::rotate(mat, glm::radians(angle), glm::vec3{ 0.0f, 1.0f, 0.0f });
		meshShader->SetMatrixUniform("uOut", mat);
		objs[10]->Draw(meshShader);
	}

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
	camera.position = glm::vec3{ 0.0f, 0.50f, 3.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	// Create shader
	meshShader = new Shader();
	if (!meshShader->Load("Shaders/mesh.vert", "Shaders/mesh.frag"))
	{
		std::cout << "Failed to load Shaders" << std::endl;
		return;
	}

	Cube* sun{ new Cube{} };
	sun->SetWorldScale(glm::vec3{ 0.6f, 0.6f, 0.6f });

	Cube* earthOne{ new Cube{} };
	earthOne->SetWorldTranslate(glm::vec3{ -1.0f, 0.0f, 0.0f });
	earthOne->SetWorldScale(glm::vec3{ 0.3f, 0.3f, 0.3f });
	Cube* moonOne{ new Cube{} };
	moonOne->SetWorldTranslate(glm::vec3{ -0.3f, 0.0f, 0.0f });
	moonOne->SetWorldScale(glm::vec3{ 0.1f, 0.1f, 0.1f });
	Orbit* orbitBigOne{ new Orbit{} };
	Orbit* orbitSmallOne{ new Orbit{} };
	orbitSmallOne->SetWorldTranslate(glm::vec3{ -1.0f, 0.0f, 0.0f });
	orbitSmallOne->SetWorldScale(glm::vec3{ 0.3f, 0.3f, 0.3f });

	Cube* earthTwo{ new Cube{} };
	earthTwo->SetWorldTranslate(glm::vec3{ -1.0f, 0.0f, 0.0f });
	earthTwo->SetWorldScale(glm::vec3{ 0.3f, 0.3f, 0.3f });
	Cube* moonTwo{ new Cube{} };
	moonTwo->SetWorldTranslate(glm::vec3{ -0.3f, 0.0f, 0.0f });
	moonTwo->SetWorldScale(glm::vec3{ 0.1f, 0.1f, 0.1f });
	Orbit* orbitBigTwo{ new Orbit{} };
	Orbit* orbitSmallTwo{ new Orbit{} };
	orbitSmallTwo->SetWorldTranslate(glm::vec3{ -1.0f, 0.0f, 0.0f });
	orbitSmallTwo->SetWorldScale(glm::vec3{ 0.3f, 0.3f, 0.3f });

	Cube* earthThree{ new Cube{} };
	earthThree->SetWorldTranslate(glm::vec3{ -1.0f, 0.0f, 0.0f });
	earthThree->SetWorldScale(glm::vec3{ 0.3f, 0.3f, 0.3f });
	Cube* moonThree{ new Cube{} };
	moonThree->SetWorldTranslate(glm::vec3{ -0.3f, 0.0f, 0.0f });
	moonThree->SetWorldScale(glm::vec3{ 0.1f, 0.1f, 0.1f });
	Orbit* orbitBigThree{ new Orbit{} };
	Orbit* orbitSmallThree{ new Orbit{} };
	orbitSmallThree->SetWorldTranslate(glm::vec3{ -1.0f, 0.0f, 0.0f });
	orbitSmallThree->SetWorldScale(glm::vec3{ 0.3f, 0.3f, 0.3f });

	objs.emplace_back(sun);
	objs.emplace_back(earthOne);
	objs.emplace_back(moonOne);
	objs.emplace_back(orbitBigOne);
	objs.emplace_back(orbitSmallOne);

	objs.emplace_back(earthTwo); // 5
	objs.emplace_back(moonTwo); // 6
	objs.emplace_back(orbitBigTwo); // 7
	objs.emplace_back(orbitSmallTwo); // 8

	objs.emplace_back(earthThree); // 9
	objs.emplace_back(moonThree); // 10
	objs.emplace_back(orbitBigThree); // 11
	objs.emplace_back(orbitSmallThree); // 12

	speedOne = Random::GetFloatRange(0.5f, 1.5f);
	speedTwo= Random::GetFloatRange(0.5f, 1.5f);
	speedThree= Random::GetFloatRange(0.5f, 1.5f);
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
