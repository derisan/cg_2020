#include "object.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

Object::Object()
	: mState{ State::kPaused },
	mPosition{ 0.0f, 0.0f, 0.0f },
	mScale{ 1.0f, 1.0f, 1.0f },
	mRotation{ 15.0f },
	mAxis{ 1.0f, -1.0f, 0.0f },
	mRecomputeWorldTransform{ true },
	mShouldRevolve{ false }
{

}

void Object::Update(float dt)
{
	if (mRecomputeWorldTransform)
		ComputeWorldTransform();
}

void Object::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform && !mShouldRevolve)
	{
		mRecomputeWorldTransform = false;

		mWorldTransform = glm::mat4{ 1.0f };
		mWorldTransform = glm::translate(mWorldTransform, mPosition);
		if(mXRotate)
			mWorldTransform = glm::rotate(mWorldTransform, glm::radians(-15.0f), glm::vec3{ 0.0f, 1.0f, 0.0f });
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), mAxis);
		mWorldTransform = glm::scale(mWorldTransform, mScale);
	}
	else if(mRecomputeWorldTransform && mShouldRevolve)
	{
		mRecomputeWorldTransform = false;

		mWorldTransform = glm::mat4{ 1.0f };
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(15.0f), glm::vec3{ 1.0f, 0.0f, 0.0f });
		mWorldTransform = glm::translate(mWorldTransform, mPosition);
		mWorldTransform = glm::scale(mWorldTransform, mScale);
	}
}

