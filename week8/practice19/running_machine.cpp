#include "running_machine.h"

#include <GL/glew.h>

#include "cube.h"
#include "cylinder.h"
#include "shader.h"

RunningMachine::RunningMachine()
	: mAngle{ 0.0f },
	mSpeed{ 1.5f }
{
	Load();
}

RunningMachine::~RunningMachine()
{
	for (auto cube : mCubes)
		delete cube;

	for (auto cy : mBelts)
		delete cy;
}

void RunningMachine::Update(float dt)
{
	if (mAngle > 30.0f)
		mSpeed = -mSpeed;
	else if (mAngle < -30.0f)
		mSpeed = -mSpeed;
	
	mAngle += mSpeed;

	for (auto cube : mCubes)
	{
		if (cube->IsZRotate())
		{
			cube->SetZRotation(mAngle);
			mAngle = -mAngle;
		}
		cube->Update(dt);
	}

	for (auto cy : mBelts)
	{
		if (cy->IsZRotate())
		{
			cy->SetZRotation(mAngle);
		}
		cy->Update(dt);
	}
}

void RunningMachine::Draw(Shader* shader)
{
	for (auto cube : mCubes)
		cube->Draw(shader);

	glDisable(GL_CULL_FACE);
	for (auto cy : mBelts)
		cy->Draw(shader);
	glEnable(GL_CULL_FACE);
}

void RunningMachine::Load()
{
	Cube* floor = new Cube{ Cube::kDefault, Object::kBlue };
	floor->SetScale(glm::vec3{ 1.0f, 0.1f, 0.5f });
	floor->SetPosition(glm::vec3{ -2.0f, 0.0f, 2.0f });
	mCubes.emplace_back(floor);

	Cube* leftArm = new Cube{ Cube::kDefault, Object::kBlue };
	leftArm->SetScale(glm::vec3{ 0.1f, 0.5f, 0.1f });
	leftArm->SetPosition(glm::vec3{ -2.45f, 0.0f, 2.2f });
	mCubes.emplace_back(leftArm);

	Cube* rightArm = new Cube{ Cube::kDefault, Object::kBlue };
	rightArm->SetScale(glm::vec3{ 0.1f, 0.5f, 0.1f });
	rightArm->SetPosition(glm::vec3{ -2.45f, 0.0f, 1.8f });
	mCubes.emplace_back(rightArm);

	Cube* mid = new Cube{ Cube::kDefault, Object::kBlue };
	mid->SetScale(glm::vec3{ 0.1f, 0.1f, 0.5f });
	mid->SetPosition(glm::vec3{ -2.45f, 0.5f, 2.0f });
	mCubes.emplace_back(mid);

	Cube* body = new Cube{ Cube::kDefault, Object::kBlue };
	body->SetScale(glm::vec3{ 0.1f, 0.5f, 0.5f });
	body->SetPosition(glm::vec3{ -2.0f, 0.5f, 2.0f });
	mCubes.emplace_back(body);

	Cube* leftLeg = new Cube{ Cube::kLeftPole, Object::kGreen};
	leftLeg->SetPosition(glm::vec3{ -2.0f, 0.5f, 2.2f });
	leftLeg->SetZRotate(true);
	mCubes.emplace_back(leftLeg);

	Cube* rightLeg = new Cube{ Cube::kRightPole, Object::kYellow};
	rightLeg->SetPosition(glm::vec3{ -2.0f, 0.5f, 1.8f });
	rightLeg->SetZRotate(true);
	mCubes.emplace_back(rightLeg);


	Cylinder* cy1 = new Cylinder{ Object::kRed };
	cy1->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy1->SetPosition(glm::vec3{ -2.4f, 0.1f, 2.0f });
	cy1->SetZRotate(true);
	mBelts.emplace_back(cy1);

	Cylinder* cy2 = new Cylinder{ Object::kRed };
	cy2->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy2->SetPosition(glm::vec3{ -2.3f, 0.1f, 2.0f });
	cy2->SetZRotate(true);
	mBelts.emplace_back(cy2);

	Cylinder* cy3 = new Cylinder{ Object::kRed };
	cy3->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy3->SetPosition(glm::vec3{ -2.2f, 0.1f, 2.0f });
	cy3->SetZRotate(true);
	mBelts.emplace_back(cy3);

	Cylinder* cy4 = new Cylinder{ Object::kRed };
	cy4->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy4->SetPosition(glm::vec3{ -2.1f, 0.1f, 2.0f });
	cy4->SetZRotate(true);
	mBelts.emplace_back(cy4);

	Cylinder* cy5 = new Cylinder{ Object::kRed };
	cy5->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy5->SetPosition(glm::vec3{ -2.0f, 0.1f, 2.0f });
	cy5->SetZRotate(true);
	mBelts.emplace_back(cy5);

	Cylinder* cy6 = new Cylinder{ Object::kRed };
	cy6->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy6->SetPosition(glm::vec3{ -1.9f, 0.1f, 2.0f });
	cy6->SetZRotate(true);
	mBelts.emplace_back(cy6);

	Cylinder* cy7 = new Cylinder{ Object::kRed };
	cy7->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy7->SetPosition(glm::vec3{ -1.8f, 0.1f, 2.0f });
	cy7->SetZRotate(true);
	mBelts.emplace_back(cy7);

	Cylinder* cy8 = new Cylinder{ Object::kRed };
	cy8->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy8->SetPosition(glm::vec3{ -1.7f, 0.1f, 2.0f });
	cy8->SetZRotate(true);
	mBelts.emplace_back(cy8);

	Cylinder* cy9 = new Cylinder{ Object::kRed };
	cy9->SetScale(glm::vec3{ 0.05f, 0.05f, 0.5f });
	cy9->SetPosition(glm::vec3{ -1.6f, 0.1f, 2.0f });
	cy9->SetZRotate(true);
	mBelts.emplace_back(cy9);
}