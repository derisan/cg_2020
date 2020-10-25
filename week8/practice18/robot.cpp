#include "robot.h"

#include "cube.h"
#include "shader.h"

Robot::Robot()
{
	Load();
}

void Robot::Update(float dt)
{
	for (auto cube : mCubes)
		cube->Update(dt);
}

void Robot::Draw(Shader* shader)
{
	for (auto cube : mCubes)
		cube->Draw(shader);
}

void Robot::Load()
{
	Cube* head{ new Cube{Object::kBlack} };
	head->SetScale(glm::vec3{ 0.2f, 0.2f, 0.2f });
	head->SetPosition(glm::vec3{ 0.05f, 0.5f, 0.05f });
	mCubes.emplace_back(head);

	Cube* nose{ new Cube{Object::kWhite} };
	nose->SetScale(glm::vec3{ 0.1f, 0.1f, 0.1f });
	nose->SetPosition(glm::vec3{ 0.25f, 0.55f, 0.10f });
	mCubes.emplace_back(nose);

	Cube* body{ new Cube{Object::kRed} };
	body->SetScale(glm::vec3{ 0.3f, 0.3f, 0.3f });
	body->SetPosition(glm::vec3{ 0.0, 0.2f, 0.0f });
	mCubes.emplace_back(body);

	Cube* leftArm{ new Cube{Object::kGreen} };
	leftArm->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	leftArm->SetPosition(glm::vec3{ 0.1f, 0.30f, -0.1f });
	mCubes.emplace_back(leftArm);

	Cube* rightArm{ new Cube{Object::kGreen} };
	rightArm->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	rightArm->SetPosition(glm::vec3{ 0.1f, 0.30f, 0.3f });
	mCubes.emplace_back(rightArm);

	Cube* leftLeg{ new Cube{Object::kBlue} };
	leftLeg->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	leftLeg->SetPosition(glm::vec3{ 0.1f, 0.0f, 0.00f });
	mCubes.emplace_back(leftLeg);

	Cube* rightLeg{ new Cube{Object::kBlue} };
	rightLeg->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	rightLeg->SetPosition(glm::vec3{ 0.1f, 0.0f, 0.2f });
	mCubes.emplace_back(rightLeg);
}

void Robot::Jump()
{

}

void Robot::Move(unsigned char key)
{

}