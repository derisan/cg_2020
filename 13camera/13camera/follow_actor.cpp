#include "follow_actor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "mesh_component.h"

FollowActor::FollowActor(Gfw* gfw, Gfw::Layer layer)
	: Actor{ gfw, layer },
	mForwardSpeed{ 0.0f },
	mRotationSpeed{ 0.0f },
	mView{ 1.0f }
{
	auto mc = new MeshComponent{ this, "Assets/chr_knight.gpmesh" };
	SetScale(0.25f);
}

void FollowActor::UpdateActor()
{
	auto pos = GetPosition();
	auto rot = GetRotation();

	pos += mForwardSpeed * GetForward() * mGfw->dt;
	rot += mRotationSpeed * mGfw->dt;
	
	auto cameraPos = pos - GetForward() * 3.0f + glm::vec3{ 0.0f, 3.0f, 0.0f };
	auto cameraTarget = pos + GetForward();

	mView = glm::lookAt(cameraPos, cameraTarget, glm::vec3{ 0.0f, 1.0f, 0.0f });

	SetPosition(pos);
	SetRotation(rot);
}

void FollowActor::ActorInput(bool* keyState, int x, int y)
{
	mForwardSpeed = 0.0f;
	mRotationSpeed = 0.0f;

	if (keyState[119]) // w
		mForwardSpeed = kMovementSpeed;

	if (keyState[115]) // s
		mForwardSpeed = -kMovementSpeed;

	if (keyState[97]) // a 
		mRotationSpeed = kRotationSpeed;

	if (keyState[100]) // d
		mRotationSpeed = -kRotationSpeed;
}