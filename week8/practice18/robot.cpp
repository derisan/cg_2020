#include "robot.h"

#include <iostream>

#include "cube.h"
#include "shader.h"

Robot::Robot()
	: mJumpSpeed{ 0.1f },
	mShouldJump{ false },
	mAngle{ 0.0f },
	mSpeed{ 1.0f }
{
	Load();
}

void Robot::Update(float dt)
{
	for (auto cube : mCubes)
		cube->Update(dt);

	if (mShouldJump)
		Jump();

	if (mAngle > 60.0f)
		mSpeed *= -1;
	if (mAngle < -60.0f)
		mSpeed *= -1;
	mAngle += mSpeed;

	Swing();
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

	Cube* leftArm{ new Cube{Cube::kLeftArm, Object::kYellow} };
	leftArm->SetZRotate(true);
	leftArm->SetPosition(glm::vec3{ 0.0f, 0.6f, 0.0f });
	mCubes.emplace_back(leftArm);

	Cube* rightArm{ new Cube{Cube::kRightArm, Object::kYellow} };
	rightArm->SetZRotate(true);
	rightArm->SetPosition(glm::vec3{ 0.0f, 0.6f, 0.0f });
	mCubes.emplace_back(rightArm);

	Cube* leftLeg{ new Cube{Cube::kLeftLeg, Object::kGreen} };
	leftLeg->SetPosition(glm::vec3{ 0.0f, 0.4f, 0.00f });
	leftLeg->SetZRotate(true);
	mCubes.emplace_back(leftLeg);

	Cube* rightLeg{ new Cube{Cube::kRightLeg, Object::kGreen} };
	rightLeg->SetPosition(glm::vec3{ 0.0f, 0.4f, 0.0f });
	rightLeg->SetZRotate(true);
	mCubes.emplace_back(rightLeg);
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

	if (key == 'w' || key == 's')
	{
		for (auto cube : mCubes)
			if (cube->IsZRotate())
			{
				cube->SetZRotate(false);
				cube->SetXRotate(true);
			}
	}

	if (key == 'a' || key == 'd')
	{
		for (auto cube : mCubes)
			if (cube->IsXRotate())
			{
				cube->SetZRotate(true);
				cube->SetXRotate(false);
			}
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

void Robot::Swing()
{
	for (auto cube : mCubes)
	{
		if (cube->IsZRotate())
		{
			cube->SetZRotation(mAngle);
			mAngle = -mAngle;
		}
		else if (cube->IsXRotate())
		{
			cube->SetXRotation(mAngle);
			mAngle = -mAngle;
		}
	}
}