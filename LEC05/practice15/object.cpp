#include "object.h"

Object::Object()
	: mState{State::kActive},
	mWorldTransform{ 1.0f },
	mAngle{ 0.0f }
{

}

void Object::Update(float dt)
{
	if (mState == State::kActive)
		mAngle += cos(dt);
}