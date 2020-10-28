#include "running_machine.h"

#include "cube.h"
#include "cylinder.h"
#include "shader.h"

RunningMachine::RunningMachine()
	: cylinder{ nullptr },
	mAngle{ 0.0f },
	mSpeed{ 1.5f }
{
	Load();
}

RunningMachine::~RunningMachine()
{
	for (auto cube : mCubes)
		delete cube;

	delete cylinder;
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

	cylinder->SetZRotation(mAngle);
	cylinder->Update(dt);
}

void RunningMachine::Draw(Shader* shader)
{
	for (auto cube : mCubes)
		cube->Draw(shader);

	cylinder->Draw(shader);
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


	cylinder = new Cylinder{ Object::kRed };
	cylinder->SetScale(glm::vec3{ 0.5f, 0.05f, 0.5f });
	//cylinder->SetZRotate(true);
	cylinder->SetPosition(glm::vec3{ -2.0f, 0.1f, 2.0f });
}