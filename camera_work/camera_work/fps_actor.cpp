#include "fps_actor.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "mesh_component.h"

FpsActor::FpsActor(Gfw* gfw, Gfw::Layer layer)
	: Actor{ gfw, layer },
	mForwardSpeed{ 0.0f },
	mStrafeSpeed{ 0.0f },
	mPitch{ 0.0f }
{
	
}

void FpsActor::UpdateActor()
{
	auto pos = GetPosition();
	pos += GetForward() * mForwardSpeed * mGfw->dt;
	pos += GetRight() * mStrafeSpeed * mGfw->dt;

	const auto& cameraPos = GetPosition();
	auto cameraTarget = cameraPos + glm::rotateX(glm::normalize(GetForward()), glm::radians(mPitch));

	mView = glm::lookAt(cameraPos, cameraTarget, glm::vec3{ 0.0f, 1.0f, 0.0f });

	SetPosition(pos);
}

void FpsActor::ActorInput(bool* keyState, int x, int y)
{
	// Need to reset speed per update
	mForwardSpeed = 0.0f;
	mStrafeSpeed = 0.0f;

	if(keyState[119]) // w
		mForwardSpeed = kSpeed;
	
	if(keyState[115]) // s
		mForwardSpeed = -kSpeed;

	if(keyState[97]) // a 
		mStrafeSpeed = -kSpeed;
		
	if(keyState[100]) // d
		mStrafeSpeed = kSpeed;

	auto rot = GetRotation();
	rot -= x / kSensitivty;
	SetRotation(rot);

	mPitch += y / kSensitivty;
	mPitch = glm::clamp(mPitch, -89.0f, 89.0f);
}