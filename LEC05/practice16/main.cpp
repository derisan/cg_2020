// -----------------------------------
// ½Ç½À16
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "shader.h"
#include "plane.h"
#include "frontplane.h"
#include "axis.h"
#include "pyramid.h"

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

float topAngle{ 0.0f };
float frontAngle{ 0.0f };
float rotateAngle{ 0.0f };
float openAngle{ 0.0f };
constexpr float speed{ 0.5f };

bool isChange{ false };
bool isRotate{ false };
bool isTopAnimPlay{ false };
bool isFrontAnimPlay{ false };
bool isPyramidOpen{ false };
bool isPerspective{ true };

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
	if(isPerspective)
		proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	else
		proj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);
	meshShader->SetMatrixUniform("uProj", proj);

	if (isRotate)
		rotateAngle += speed;

	// axis
	glm::mat4 mat{ 1.0f };
	mat = glm::rotate(mat, glm::radians(30.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
	meshShader->SetMatrixUniform("uOut", mat);
	objs[0]->Draw(meshShader);

	mat = glm::rotate(mat, glm::radians(rotateAngle), glm::vec3{ 0.0f, 1.0f, 0.0f });
	meshShader->SetMatrixUniform("uOut", mat);

	// Draw Cube
	if (!isChange)
	{
		if (isTopAnimPlay)
			topAngle += speed;

		if (isFrontAnimPlay)
		{
			frontAngle += speed;
			if (frontAngle > 90.0f)
				frontAngle = 90.0f;
		}
		else
		{
			frontAngle -= speed;
			if (frontAngle < 0.0f)
				frontAngle = 0.0f;
		}

		// bottom-side
		objs[3]->Draw(meshShader);

		// left-side
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ -0.5f, 0.5f, 0.0f });
		mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3{ 0.0f, 0.0f, 1.0f });
		objs[4]->SetWorldTransform(mat);
		objs[4]->Draw(meshShader);

		// right-side
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ 0.5f, 0.5f, 0.0f });
		mat = glm::rotate(mat, glm::radians(-90.0f), glm::vec3{ 0.0f, 0.0f, 1.0f });
		objs[5]->SetWorldTransform(mat);
		objs[5]->Draw(meshShader);

		// back-side
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ 0.0f, 0.5f, -0.5f });
		mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
		objs[6]->SetWorldTransform(mat);
		objs[6]->Draw(meshShader);

		// top-side
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ 0.0f, 1.0f, 0.0f });
		mat = glm::rotate(mat, glm::radians(topAngle), glm::vec3{ 1.0f, 0.0f, 0.0f });
		objs[1]->SetWorldTransform(mat);
		objs[1]->Draw(meshShader);

		// front-side
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ 0.0f, 0.0f, 0.5f });
		mat = glm::rotate(mat, glm::radians(frontAngle), glm::vec3{ 1.0f, 0.0f, 0.0f });
		objs[2]->SetWorldTransform(mat);
		objs[2]->Draw(meshShader);
	}
	// Let's draw pyramid
	else
	{
		if (isPyramidOpen)
		{
			openAngle += speed;
			if (openAngle > 117.0f)
				openAngle = 117.0f;
		}
		else
		{
			openAngle -= speed;
			if (openAngle < 0.0f)
				openAngle = 0.0f;
		}

		objs[3]->Draw(meshShader);

		// front
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ -0.5f, 0.0f, 0.0f });
		mat = glm::rotate(mat, glm::radians(openAngle), glm::vec3{ 0.0f, 0.0f, 1.0f });
		objs[7]->SetWorldTransform(mat);
		objs[7]->Draw(meshShader);

		// back
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ 0.5f, 0.0f, 0.0f });
		mat = glm::rotate(mat, glm::radians(openAngle), glm::vec3{ 0.0f, 0.0f, -1.0f });
		objs[8]->SetWorldTransform(mat);
		objs[8]->Draw(meshShader);

		// left
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ 0.0f, 0.0f, -0.5f });
		mat = glm::rotate(mat, glm::radians(openAngle), glm::vec3{ -1.0f, 0.0f, 0.0f });
		objs[9]->SetWorldTransform(mat);
		objs[9]->Draw(meshShader);

		// right
		mat = glm::mat4{ 1.0f };
		mat = glm::translate(mat, glm::vec3{ 0.0f, 0.0f, 0.5f });
		mat = glm::rotate(mat, glm::radians(openAngle), glm::vec3{ 1.0f, 0.0f, 0.0f });
		objs[10]->SetWorldTransform(mat);
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
		case 't': case 'T':
			isTopAnimPlay = !isTopAnimPlay;
			break;
		case 'f': case 'F':
			isFrontAnimPlay = !isFrontAnimPlay;
			break;
		case 'o': case 'O':
			isPyramidOpen = !isPyramidOpen;
			break;
		case 'p': case 'P':
			isPerspective = !isPerspective;
			break;
		case 'z': case 'Z':
		case 'x': case 'X':
		case 'w': case 'W':
		case 's': case 'S':
		case 'a': case 'A':
		case 'd': case 'D':
			MoveObjects(key);
			break;
		case 'c': case 'C':
			isChange = !isChange;
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
	//objs.clear();

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

	objs.emplace_back(new Axis{});		// axis

	// Cube planes
	objs.emplace_back(new Plane{Plane::kRed});		// top
	objs.emplace_back(new FrontPlane{Plane::kGreen});// front
	objs.emplace_back(new Plane{Plane::kMagenta});		// bottom 3
	objs.emplace_back(new Plane{Plane::kYellow});		// left 4
	objs.emplace_back(new Plane{Plane::kBlue});		// right 5
	objs.emplace_back(new Plane{Plane::kCyan});		// back 6

	// Pyramid planes
	objs.emplace_back(new Pyramid{ Pyramid::kFront }); // 7
	objs.emplace_back(new Pyramid{ Pyramid::kBack }); // 8
	objs.emplace_back(new Pyramid{ Pyramid::kLeft }); // 9
	objs.emplace_back(new Pyramid{ Pyramid::kRight }); // 10
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
