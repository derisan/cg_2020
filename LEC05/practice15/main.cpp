// -----------------------------------
// ½Ç½À15
// 2016180007 ±è¸í±Ô
// -----------------------------------

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "utils.h"
#include "shader.h"
#include "object.h"
#include "orbit.h"
#include "planet.h"
#include "earth.h"

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
void MoveCamera(unsigned char key);
void RotateObjects();
void StopObjects();

Shader* meshShader{ nullptr };
std::vector<Object*> objs;

auto drawMode = GL_FILL;

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

	// Set view & proj matrix
	meshShader->SetActive();
	glm::mat4 view{ 1.0f };
	view = glm::lookAt(camera.position, camera.position + camera.target, camera.up);
	meshShader->SetMatrixUniform("uView", view);

	glm::mat4 proj{ 1.0f };
	proj = glm::perspective(45.0f, static_cast<float>(kScrWidth) / static_cast<float>(kScrHeight), 0.1f, 100.0f);
	meshShader->SetMatrixUniform("uProj", proj);


	for (auto obj : objs)
	{
		obj->Update(dt);
		obj->Draw(meshShader);
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
			RotateObjects();
			break;
		case 'z': case 'Z':
		case 'x': case 'X':
		case 'w': case 'W':
		case 's': case 'S':
		case 'a': case 'A':
		case 'd': case 'D':
			MoveCamera(key);
			break;
		case 'c': case 'C':
			StopObjects();
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
	objs.clear();

	delete meshShader;

	glutLeaveMainLoop();
}

void LoadData()
{
	// Set cameara elements
	camera.position = glm::vec3{ 0.0f, 0.5f, 3.0f };
	camera.target = glm::vec3{ 0.0f, 0.0f, -1.0f };
	camera.up = glm::vec3{ 0.0f, 1.0f, 0.0f };

	// Create shader
	meshShader = new Shader();
	if (!meshShader->Load("Shaders/mesh.vert", "Shaders/mesh.frag"))
	{
		std::cout << "Failed to load Shaders" << std::endl;
		return;
	}

	// Create 3 Orbit
	auto orbit_xz{ new Orbit{} };
	auto orbit_45{ new Orbit{} };
	auto orbit_minus_45{ new Orbit{} };
	orbit_45->SetRotation(45.0f);
	orbit_45->SetAxis(glm::vec3{ 0.0f, 0.0f, 1.0f });
	orbit_minus_45->SetRotation(-45.0f);
	orbit_minus_45->SetAxis(glm::vec3{ 0.0f, 0.0f, 1.0f });

	objs.emplace_back(orbit_xz);
	objs.emplace_back(orbit_45);
	objs.emplace_back(orbit_minus_45);

	// Create sun
	auto sun{ new Planet{} };
	sun->SetScale(0.3f);
	objs.emplace_back(sun);

	// Create 3 earth
	auto earth_one{ new Earth() };
	earth_one->SetPosition(glm::vec3{ 1.5f, 0.0f, 0.0f });
	earth_one->SetRevAxis(glm::vec3{ 0.0f, 1.0f, 0.0f });
	objs.emplace_back(earth_one);

	auto earth_two{ new Earth() };
	earth_two->SetPosition(glm::vec3{ 0.0f, 0.0f, 1.5f });
	glm::vec3 orbit{ 0.0f, 1.0f, 0.0f };
	orbit = glm::rotate(orbit, glm::radians(45.0f), glm::vec3{ 0.0f, 0.0f, 1.0f });
	earth_two->SetRevAxis(orbit);
	objs.emplace_back(earth_two);

	auto earth_three{ new Earth() };
	earth_three->SetPosition(glm::vec3{ 0.0f, 0.0f, -1.5f });
	orbit = glm::vec3{ 0.0f, 1.0f, 0.0f };
	orbit = glm::rotate(orbit, glm::radians(-45.0f), glm::vec3{ 0.0f, 0.0f, 1.0f });
	earth_three->SetRevAxis(orbit);
	objs.emplace_back(earth_three);

	// Create moon's orbit
	auto orbit_moon_one{ new Orbit{} };
	orbit_moon_one->SetScale(0.15f);
	orbit_moon_one->SetPosition(glm::vec3{ 1.5f, 0.0f, 0.0f });
	objs.emplace_back(orbit_moon_one);

	auto orbit_moon_two{ new Orbit{} };
	orbit_moon_two->SetScale(0.15f);
	orbit_moon_two->SetPosition(glm::vec3{ 0.0f, 0.0f, 1.5f });
	orbit_moon_two->SetRotation(45.0f);
	orbit_moon_two->SetAxis(glm::vec3{ 0.0f, 0.0f, 1.0f });
	objs.emplace_back(orbit_moon_two);

	auto orbit_moon_three{ new Orbit{} };
	orbit_moon_three->SetScale(0.15f);
	orbit_moon_three->SetPosition(glm::vec3{ 0.0f, 0.0f, -1.5f });
	orbit_moon_three->SetRotation(-45.0f);
	orbit_moon_three->SetAxis(glm::vec3{ 0.0f, 0.0f, 1.0f });
	objs.emplace_back(orbit_moon_three);
}

void ChangeDrawStyle()
{
	if (drawMode == GL_LINE)
		drawMode = GL_FILL;
	else
		drawMode = GL_LINE;
		
	glPolygonMode(GL_FRONT_AND_BACK, drawMode);
}

void MoveCamera(unsigned char key)
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

void RotateObjects()
{
	for (auto obj : objs)
		obj->SetState(Object::State::kActive);
}

void StopObjects()
{
	for (auto obj : objs)
		obj->SetState(Object::State::kPaused);
}