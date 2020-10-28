#include "tree.h"

#include <iostream>

#include "cube.h"
#include "shader.h"

Tree::Tree()
	: mRoot{ nullptr },
	mBush{ nullptr },
	mSpeed{ 0.01f }
{
	Load();
}

Tree::~Tree()
{
	delete mRoot;
	delete mBush;
}

void Tree::Update(float dt)
{
	ScalingBush(dt);

	mRoot->Update(dt);
	mBush->Update(dt);
}

void Tree::Draw(Shader* shader)
{
	mRoot->Draw(shader);
	mBush->Draw(shader);
}

void Tree::Load()
{
	mBush = new Cube{ Cube::kDefault, Object::kGreen };
	mBush->SetPosition(glm::vec3{ 2.0f, 1.0f, 2.0f });
	mBush->SetScale(glm::vec3{ 0.5f, 0.5f, 0.5f });

	mRoot = new Cube{ Cube::kDefault, Object::kBrown };
	mRoot->SetPosition(glm::vec3{ 2.0f, 0.0f, 2.0f });
	mRoot->SetScale(glm::vec3{ 0.3f, 1.0f, 0.3f });
}

void Tree::ScalingBush(float dt)
{
	glm::vec3 scale{ mBush->GetScale() };
	
	mSpeed += dt;
	
	scale.x += cos(mSpeed) * 0.0025f;
	scale.y += cos(mSpeed) * 0.0025f;
	scale.z += cos(mSpeed) * 0.0025f;

	mBush->SetScale(scale);
}