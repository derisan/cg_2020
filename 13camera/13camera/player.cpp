#include "player.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "mesh_component.h"

Player::Player(Gfw* gfw, Gfw::Layer layer)
	: Actor{ gfw, layer },
	mForwardSpeed{ 0.0f },
	mRotationSpeed{ 0.0f },
	mStrafeSpeed{ 0.0f },
	mViewOption{ ViewOption::kFollow },
	mView{ 1.0f }
{
	auto mc = new MeshComponent{ this, "Assets/chr_knight.gpmesh" };
	SetScale(0.5f);
	SetPosition(glm::vec3{ 0.0f, -1.0f, 0.0f });
}

void Player::UpdateActor()
{
	if (ViewOption::kFollow == mViewOption)
	{
		auto pos = GetPosition();
		auto rot = GetRotation();

		pos += mForwardSpeed * GetForward() * mGfw->dt;
		rot += mRotationSpeed * mGfw->dt;

		auto cameraPos = pos - GetForward() * 3.0f + glm::vec3{ 0.0f, 3.0f, 0.0f };
		auto cameraTarget = pos + GetForward() * 3.0f;

		mView = glm::lookAt(cameraPos, cameraTarget, glm::vec3{ 0.0f, 1.0f, 0.0f });

		SetPosition(pos);
		SetRotation(rot);
	}
	else
	{
		auto pos = GetPosition();
		pos += GetForward() * mForwardSpeed * mGfw->dt;
		pos += GetRight() * mStrafeSpeed * mGfw->dt;

		auto cameraPos = GetPosition() + glm::vec3{ 0.0f, 1.0f, 0.0f };
		auto cameraTarget = cameraPos + GetForward();

		mView = glm::lookAt(cameraPos, cameraTarget, glm::vec3{ 0.0f, 1.0f, 0.0f });

		SetPosition(pos);
	}
}

void Player::ActorInput(bool* keyState, int x, int y)
{
	mForwardSpeed = 0.0f;
	mRotationSpeed = 0.0f;
	mStrafeSpeed = 0.0f;
	
	if (ViewOption::kFollow == mViewOption)
	{
		if (keyState[119]) // w
			mForwardSpeed = kMovementSpeed;

		if (keyState[115]) // s
			mForwardSpeed = -kMovementSpeed;

		if (keyState[97]) // a 
			mRotationSpeed = kRotationSpeed;

		if (keyState[100]) // d
			mRotationSpeed = -kRotationSpeed;
	}
	else
	{
		if (keyState[119]) // w
			mForwardSpeed = kMovementSpeed;

		if (keyState[115]) // s
			mForwardSpeed = -kMovementSpeed;

		if (keyState[97]) // a 
			mStrafeSpeed = -kMovementSpeed;

		if (keyState[100]) // d
			mStrafeSpeed = kMovementSpeed;

		auto rot = GetRotation();
		rot -= x / kSensitivty;
		SetRotation(rot);
	}
}