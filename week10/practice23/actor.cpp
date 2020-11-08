#include "actor.h"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "game.h"

Actor::Actor(Game* game)
	: mGame{ game },
	mState{ State::kActive },
	mWorldTransform{ 1.0f },
	mPosition{ 0.0f },
	mScale{ 1.0f },
	mRotation{ 0.0f },
	mAxis{ 0.0f, 1.0f, 0.0f },
	mRecomputeWorldTransform{ true }
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
}

void Actor::Update()
{
	if (mState == State::kActive)
	{
		ComputeWorldTransform();

		UpdateActor();

		ComputeWorldTransform();
	}
}

void Actor::ProcessInput(unsigned char key)
{
	if (mState == State::kActive)
	{
		ActorInput(key);
	}
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mWorldTransform = glm::mat4{ 1.0f };
		mWorldTransform = glm::translate(mWorldTransform, mPosition);
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), mAxis);
		mWorldTransform = glm::scale(mWorldTransform, glm::vec3{ mScale });
	}
}

glm::vec3 Actor::GetForward() const
{
	return glm::rotateY(glm::vec3{ 0.0, 0.0f, -1.0f }, glm::radians(mRotation));
}

glm::vec3 Actor::GetRight() const
{
	return glm::rotateY(glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::radians(mRotation - 90.0f));
}