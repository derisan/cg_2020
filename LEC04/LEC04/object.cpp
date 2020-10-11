#include "object.h"

#include <glm/gtc/matrix_transform.hpp>

Object::Object()
	: mState{ State::kActive },
	mPosition{ 0.0f, 0.0f, 0.0f },
	mScale{ 1.0f, 1.0f, 1.0f },
	mRotation{ 0.0f },
	mAxis{ 0.0f, 0.0f, 1.0f },
	mRecomputeWorldTransform{ true }
{

}

void Object::Update(float dt)
{
	if (mRecomputeWorldTransform)
		ComputeWorldTransform();
}

void Object::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mWorldTransform = glm::mat4{ 1.0f };
		mWorldTransform = glm::translate(mWorldTransform, mPosition);
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), mAxis);
		mWorldTransform = glm::scale(mWorldTransform, mScale);
	}
}