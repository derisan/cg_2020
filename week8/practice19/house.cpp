#include "house.h"

#include <glm/geometric.hpp>

#include "cube.h"
#include "shader.h"
#include "robot.h"

House::House()
{
	Load();
}

House::~House()
{
	for (auto cube : mCubes)
		delete cube;
}

void House::Update(float dt)
{
	for (auto cube : mCubes)
		cube->Update(dt);
}

void House::Draw(Shader* shader)
{
	for (auto cube : mCubes)
		cube->Draw(shader);
}

void House::Load()
{
	Cube* bottom{ new Cube{Cube::kDefault, Object::kMagenta} };
	bottom->SetScale(glm::vec3{ 0.7f, 0.7f, 0.7f });
	mCubes.emplace_back(bottom);

	Cube* roof{ new Cube{Cube::kDefault, Object::kRed} };
	roof->SetScale(glm::vec3{ 1.0f, 0.5f, 1.0f });
	roof->SetPosition(glm::vec3{ 0.0f, 0.7f, 0.0f });
	mCubes.emplace_back(roof);

	Cube* top{ new Cube{Cube::kDefault, Object::kGreen} };
	top->SetScale(glm::vec3{ 0.5f, 0.5f, 0.5f });
	top->SetPosition(glm::vec3{ 0.0f, 1.2f, 0.0f });
	mCubes.emplace_back(top);
}

bool House::Collides(Robot* robot)
{
	glm::vec3 robotPos = robot->GetPos();

	if (glm::distance(robotPos, glm::vec3{ 0.0f, 0.0f, 0.0f }) < 0.7f)
		return true;
	else
		return false;
}