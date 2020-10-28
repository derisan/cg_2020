#include "benchpress.h"

#include "sphere.h"
#include "cube.h"
#include "shader.h"

BenchPress::BenchPress()
	: mAngle{ 0.0f },
	mRotationSpeed{ 1.5f },
	mMoveSpeed{ 0.0066f }
{
	Load();
}

BenchPress::~BenchPress()
{
	for (auto sphere : mSpheres)
		delete sphere;

	for (auto cube : mCubes)
		delete cube;
}

void BenchPress::Update(float dt)
{
	if (mAngle > 90.0f)
		mRotationSpeed = -mRotationSpeed;
	if (mAngle < 0.0f)
		mRotationSpeed = -mRotationSpeed;

	mAngle += mRotationSpeed;

	Move();

	for (auto sphere : mSpheres)
		sphere->Update(dt);

	for (auto cube : mCubes)
	{
		if (cube->IsZRotate())
		{
			cube->SetZRotation(mAngle);
			mAngle = -mAngle;
		}
		cube->Update(dt);
	}
}

void BenchPress::Draw(Shader* shader)
{
	for (auto sphere : mSpheres)
		sphere->Draw(shader);

	for (auto cube : mCubes)
		cube->Draw(shader);
}

void BenchPress::Load()
{
	Sphere* left{ new Sphere{Object::kRed} };
	left->SetPosition(glm::vec3{ -2.4f, 0.5f, -2.0f });
	left->SetScale(glm::vec3{ 0.1f, 0.5f, 0.5f });
	mSpheres.push_back(left);

	Sphere* right{ new Sphere{Object::kRed} };
	right->SetPosition(glm::vec3{ -1.6f, 0.5f, -2.0f });
	right->SetScale(glm::vec3{ 0.1f, 0.5f, 0.5f });
	mSpheres.push_back(right);

	Cube* linkPole{ new Cube{Cube::kDefault, Object::kBlue} };
	linkPole->SetScale(glm::vec3{ 1.0f, 0.05f, 0.05f });
	linkPole->SetPosition(glm::vec3{ -2.0f, 0.5f, -2.0f });
	mCubes.push_back(linkPole);

	Cube* floor{ new Cube{Cube::kDefault, Object::kBlue} };
	floor->SetScale(glm::vec3{ 1.0f, 0.1f, 1.0f });
	floor->SetPosition(glm::vec3{ -2.0f, 0.0f, -2.0f });
	mCubes.push_back(floor);

	Cube* leftPole{ new Cube{Cube::kDefault, Object::kBlue} };
	leftPole->SetScale(glm::vec3{ 0.1f, 0.5f, 0.1f });
	leftPole->SetPosition(glm::vec3{ -2.4f, 0.0f, -2.4f });
	mCubes.push_back(leftPole);

	Cube* rightPole{ new Cube{Cube::kDefault, Object::kBlue} };
	rightPole->SetScale(glm::vec3{ 0.1f, 0.5f, 0.1f });
	rightPole->SetPosition(glm::vec3{ -1.6f, 0.0f, -2.4f });
	mCubes.push_back(rightPole);

	Cube* body{ new Cube{Cube::kDefault, Object::kGreen} };
	body->SetScale(glm::vec3{ 0.5f, 0.1f, 0.7f });
	body->SetPosition(glm::vec3{ -2.0f, 0.1f, -2.0f });
	mCubes.push_back(body);

	Cube* leftArm{ new Cube{Cube::kDefault, Object::kGreen} };
	leftArm->SetScale(glm::vec3{ 0.1f, 0.4f, 0.1f });
	leftArm->SetPosition(glm::vec3{ -2.2f, 0.1f, -2.0f });
	leftArm->SetZRotate(true);
	mCubes.push_back(leftArm);

	Cube* rightArm{ new Cube{Cube::kDefault, Object::kGreen} };
	rightArm->SetScale(glm::vec3{ 0.1f, 0.4f, 0.1f });
	rightArm->SetPosition(glm::vec3{ -1.8f, 0.1f, -2.0f });
	rightArm->SetZRotate(true);
	mCubes.push_back(rightArm);
}

void BenchPress::Move()
{
	glm::vec3 pos;
	for (auto sphere : mSpheres)
	{
		pos = sphere->GetPosition();
		pos.y += mMoveSpeed;
		sphere->SetPosition(pos);
	}

	pos = mCubes[0]->GetPosition();
	pos.y += mMoveSpeed;
	mCubes[0]->SetPosition(pos);

	if (pos.y > 0.5f)
		mMoveSpeed = -mMoveSpeed;
	
	if (pos.y < 0.1f)
		mMoveSpeed = -mMoveSpeed;
}