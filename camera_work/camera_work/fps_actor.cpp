#include "fps_actor.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "mesh_component.h"

FpsActor::FpsActor(Gfw* gfw, Gfw::Layer layer)
	: Actor{ gfw, layer },
	mForwardSpeed{ 0.0f },
	mStrafeSpeed{ 0.0f },
	mView{ 1.0f }
{
	auto mc = new MeshComponent{ this, "Assets/bunny.gpmesh" };
}

void FpsActor::UpdateActor()
{
	mView = glm::mat4{ 1.0f };

	auto pos = GetPosition();
	pos += GetForward() * mForwardSpeed * mGfw->dt;
	pos += GetRight() * mStrafeSpeed * mGfw->dt;

	SetPosition(pos);

	// Need to reset speed per update
	mForwardSpeed = 0.0f;
	mStrafeSpeed = 0.0f;
}

void FpsActor::ActorInput(unsigned char key)
{
	switch (key)
	{
		case 'w': case 'W':
			mForwardSpeed = kSpeed;
			break;
		case 's': case 'S':
			mForwardSpeed = -kSpeed;
			break;
		case 'a': case 'A':
			mStrafeSpeed = -kSpeed;
			break;
		case 'd': case 'D':
			mStrafeSpeed = kSpeed;
			break;
	}
}