#include "object.h"

#include <iostream>

#include "object_manager.h"

Object::Object(ObjectManager* manager)
	: mManager{ manager },
	mState{ State::kActive },
	mXSpeed{ 0.0f },
	mYSpeed{ 0.0f },
	mShouldGravityWork{ false },
	mGravity{ 0.0f }
{
	mManager->AddObj(this);
}

Object::~Object()
{
	mManager->RemoveObj(this);
}

void Object::Update()
{
	if (mShouldGravityWork)
	{
		mGravity -= 0.0000025f;
		mYSpeed += mGravity;
	}
}

