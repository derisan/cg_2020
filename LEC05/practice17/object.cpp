#include "object.h"

Object::Object(Color color)
	: mState{State::kActive},
	mWorldTransform{ 1.0f },
	mPosition{ 0.0f },
	mScale{ 1.0f },
	mRotation{ 0.0f },
	mColor{},
	mRecomputeWorldTransform{ true }
{
	switch (color)
	{
	case kRed: // Red
		mColor = glm::vec3{ 1.0f, 0.0f, 0.0f };
		break;
	case kGreen: // Green
		mColor = glm::vec3{ 0.0f, 1.0f, 0.0f };
		break;
	case kBlue: // Blue
		mColor = glm::vec3{ 0.0f, 0.0f, 1.0f };
		break;
	case kYellow: // Yellow
		mColor = glm::vec3{ 1.0f, 1.0f, 0.0f };
		break;
	case kMagenta: // Magenta
		mColor = glm::vec3{ 1.0f, 0.0f, 1.0f };
		break;
	case kCyan: // Cyan
		mColor = glm::vec3{ 0.0f, 1.0f, 1.0f };
		break;
	case kBlack: // Black
		mColor = glm::vec3{ 0.0f, 0.0f, 0.0f };
		break;
	}
}

void Object::Update(float dt)
{
	if (mState == State::kActive && mRecomputeWorldTransform)
		ComputeWorldTransform();
}

void Object::ComputeWorldTransform()
{
	mRecomputeWorldTransform = false;

	mWorldTransform = glm::mat4{ 1.0f };
	mWorldTransform = glm::translate(mWorldTransform, mPosition);
	mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mRotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
	mWorldTransform = glm::scale(mWorldTransform, mScale);
}

