#include "pole.h"

#include "cube.h"
#include "shader.h"


Pole::Pole()
	: mAngle{ 0.0f }
{
	Load();
}

Pole::~Pole()
{
	for (auto cube : mCubes)
		delete cube;
}

void Pole::Update(float dt)
{
	mAngle += dt * 100;

	for (auto cube : mCubes)
	{
		if (cube->IsZRotate())
			cube->SetZRotation(mAngle);
		cube->Update(dt);
	}
}

void Pole::Draw(Shader* shader)
{
	for (auto cube : mCubes)
		cube->Draw(shader);
}

void Pole::Load()
{
	Cube* leftPole = new Cube{ Cube::kDefault, Object::kBlue };
	leftPole->SetPosition(glm::vec3{ 1.5f, 0.0f, -2.0f });
	leftPole->SetScale(glm::vec3{ 0.1f, 1.0f, 0.1f });
	mCubes.emplace_back(leftPole);

	Cube* rightPole = new Cube{ Cube::kDefault, Object::kBlue };
	rightPole->SetPosition(glm::vec3{ 1.5f, 0.0f, -1.0f });
	rightPole->SetScale(glm::vec3{ 0.1f, 1.0f, 0.1f });
	mCubes.emplace_back(rightPole);

	Cube* midPole = new Cube{ Cube::kDefault, Object::kBlue };
	midPole->SetPosition(glm::vec3{ 1.5f, 0.9f, -1.5f });
	midPole->SetScale(glm::vec3{ 0.1f, 0.1f, 1.0f });
	mCubes.emplace_back(midPole);

	Cube* leftArmPole = new Cube{ Cube::kLeftPole, Object::kBlue };
	leftArmPole->SetPosition(glm::vec3{ 1.5f, 0.95f, -1.7f });
	leftArmPole->SetZRotate(true);
	mCubes.emplace_back(leftArmPole);

	Cube* rightArmPole = new Cube{ Cube::kRightPole, Object::kBlue };
	rightArmPole->SetPosition(glm::vec3{ 1.5f, 0.95f, -1.3f });
	rightArmPole->SetZRotate(true);
	mCubes.emplace_back(rightArmPole);

	Cube* bodyPole = new Cube{ Cube::kBodyPole, Object::kBlue };
	bodyPole->SetPosition(glm::vec3{ 1.5f, 0.95f, -1.5f });
	bodyPole->SetZRotate(true);
	mCubes.emplace_back(bodyPole);

	Cube* headPole = new Cube{ Cube::kBodyPole, Object::kMagenta};
	headPole->SetPosition(glm::vec3{ 1.5f, 0.95f, -1.5f });
	headPole->SetScale(glm::vec3{ 0.5f, 0.5f, 0.5f });
	headPole->SetZRotate(true);
	mCubes.emplace_back(headPole);
}