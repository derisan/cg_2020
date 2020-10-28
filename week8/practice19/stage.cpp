#include "stage.h"

#include "plane.h"
#include "shader.h"

Stage::Stage()
	: mFrontIdx{ 0 },
	mShouldOpenFront{ false }
{
	Load();
}

Stage::~Stage()
{
	for (auto plane : mPlanes)
		delete plane;
}

void Stage::Update(float dt)
{
	for (auto plane : mPlanes)
		plane->Update(dt);

	if (mShouldOpenFront)
		Slide();
}

void Stage::Draw(Shader* shader)
{
	for (auto plane : mPlanes)
		plane->Draw(shader);
}

void Stage::Load()
{
	Plane* bottom{ new Plane{Object::kGray} };
	bottom->SetScale(glm::vec3{ 5.0f, 1.0f, 5.0f });
	bottom->SetXRotate(true);
	bottom->SetXRotation(180.0f);
	mPlanes.emplace_back(bottom);

	Plane* top{ new Plane{Object::kGray} };
	top->SetPosition(glm::vec3{ 0.0f, 3.0f, 0.0f });
	top->SetScale(glm::vec3{ 5.0f, 1.0f, 5.0f });
	mPlanes.emplace_back(top);

	Plane* left{ new Plane{Object::kWhite} };
	left->SetZRotate(true);
	left->SetZRotation(90.0f);
	left->SetPosition(glm::vec3{ -2.5f, 1.5f, 0.0f });
	left->SetScale(glm::vec3{ 3.0f, 1.0f, 5.0f });
	mPlanes.emplace_back(left);

	Plane* right{ new Plane{Object::kWhite} };
	right->SetZRotate(true);
	right->SetZRotation(-90.0f);
	right->SetPosition(glm::vec3{ 2.5f, 1.5f, 0.0f });
	right->SetScale(glm::vec3{ 3.0f, 1.0f, 5.0f });
	mPlanes.emplace_back(right);
	
	Plane* back{ new Plane{Object::kDarkGray} };
	back->SetXRotate(true);
	back->SetXRotation(-90.0f);
	back->SetPosition(glm::vec3{ 0.0f, 1.5f, -2.5f });
	back->SetScale(glm::vec3{ 5.0f, 1.0f, 3.0f });
	mPlanes.emplace_back(back);

	Plane* front{ new Plane{Object::kDarkGray} };
	front->SetXRotate(true);
	front->SetXRotation(-90.0f);
	front->SetPosition(glm::vec3{ 0.0f, 1.5f, 2.5f });
	front->SetScale(glm::vec3{ 5.0f, 1.0f, 3.0f });
	mPlanes.emplace_back(front);

	mFrontIdx = mPlanes.size() - 1;
}

void Stage::Slide()
{
	glm::vec3 pos{ mPlanes[mFrontIdx]->GetPosition() };
	if (pos.y > 4.0f)
	{
		mShouldOpenFront = false;
		return;
	}

	pos += glm::vec3{ 0.0f, 0.025f, 0.0f };
	mPlanes[mFrontIdx]->SetPosition(pos);
}