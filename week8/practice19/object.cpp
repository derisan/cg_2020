#include "object.h"

Object::Object(Color color)
	: mState{State::kActive},
	mWorldTransform{ 1.0f },
	mPosition{ 0.0f },
	mScale{ 1.0f },
	mYRotation{ 0.0f },
	mColor{},
	mRecomputeWorldTransform{ true },
	mIsRotateX{ false },
	mIsRotateZ{ false },
	mXRotation{ 0.0f },
	mZRotation{ 0.0f }
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
	case kWhite:
		mColor = glm::vec3{ 1.0f, 1.0f, 1.0f };
		break;
	case kGray:
		mColor = glm::vec3{ 0.65f, 0.65f, 0.65f };
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
	if (mIsRotateX)
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mXRotation), glm::vec3(1.0f, 0.0f, 0.0f));
	if(mIsRotateZ)
		mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mZRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	mWorldTransform = glm::rotate(mWorldTransform, glm::radians(mYRotation), glm::vec3{ 0.0f, 1.0f, 0.0f });
	mWorldTransform = glm::scale(mWorldTransform, mScale);
}

