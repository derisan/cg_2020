#include "robot.h"

#include <iostream>

#include "cube.h"
#include "shader.h"

Robot::Robot()
	: mJumpSpeed{ 0.1f },
	mShouldJump{ false }
{
	Load();
}

void Robot::Update(float dt)
{
	for (auto cube : mCubes)
		cube->Update(dt);

	if (mShouldJump)
		Jump();
}

void Robot::Draw(Shader* shader)
{
	for (auto cube : mCubes)
		cube->Draw(shader);
}

void Robot::Load()
{
	Cube* head{ new Cube{Cube::kHead, Object::kBlack} };
	mCubes.emplace_back(head);

	Cube* nose{ new Cube{Cube::kNose, Object::kWhite} };
	mCubes.emplace_back(nose);
	
	Cube* body{ new Cube{Cube::kBody, Object::kRed} };
	mCubes.emplace_back(body);

	//Cube* leftArm{ new Cube{Object::kYellow} };
	//leftArm->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	//leftArm->SetPosition(glm::vec3{ 0.1f, 0.30f, -0.1f });
	//leftArm->SetZRotate(true);
	//mCubes.emplace_back(leftArm);

	//Cube* rightArm{ new Cube{Object::kYellow} };
	//rightArm->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	//rightArm->SetPosition(glm::vec3{ 0.1f, 0.30f, 0.3f });
	//rightArm->SetZRotate(true);
	//mCubes.emplace_back(rightArm);

	//Cube* leftLeg{ new Cube{Object::kBlue} };
	//leftLeg->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	//leftLeg->SetPosition(glm::vec3{ 0.1f, 0.0f, 0.00f });
	//leftLeg->SetZRotate(true);
	//mCubes.emplace_back(leftLeg);

	//Cube* rightLeg{ new Cube{Object::kBlue} };
	//rightLeg->SetScale(glm::vec3{ 0.1f, 0.2f, 0.1f });
	//rightLeg->SetPosition(glm::vec3{ 0.1f, 0.0f, 0.2f });
	//rightLeg->SetZRotate(true);
	//mCubes.emplace_back(rightLeg);
}

void Robot::Jump()
{
	for (auto cube : mCubes)
	{
		glm::vec3 pos{ cube->GetPosition() };
		pos.y += mJumpSpeed;
		cube->SetPosition(pos);
	}
	mJumpSpeed -= mGravity;

	if (mJumpSpeed < 0 && mCubes[0]->GetPosition().y < 0.1f)
	{
		std::cout << "asdf" << std::endl;
		mShouldJump = false;
		mJumpSpeed = 0.1f;
	}
}

void Robot::Move(unsigned char key)
{
	float forwardSpeed{ 0.0f };
	float strafeSpeed{ 0.0f };
	float dir{ 0.0f };

	switch (key)
	{
		case 'w': case 'W':
			forwardSpeed -= 0.1f;
			dir = 90.0f;
			break;
		case 's': case 'S':
			forwardSpeed += 0.1f;
			dir = 270.0f;
			break;
		case 'a': case 'A':
			strafeSpeed -= 0.1f;
			dir = 180.0f;
			break;
		case 'd': case 'D':
			strafeSpeed += 0.1f;
			dir = 0.0f;
			break;
	}

	for (auto cube : mCubes)
	{
		glm::vec3 pos{ cube->GetPosition() };
		pos.x += strafeSpeed;
		pos.z += forwardSpeed;

		cube->SetYRotation(dir);
		cube->SetPosition(pos);
	}
}