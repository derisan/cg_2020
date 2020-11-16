#include "camera_component.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "actor.h"

CameraComponent::CameraComponent(Actor* owner)
	: Component{ owner },
	mCameraPos{ 0.0f },
	mCameraTarget{ 0.0f },
	mCameraUp{ 0.0f, 1.0f, 0.0f },
	mView{ 1.0f },
	mSensitivity{ 5.0f },
	mPitch{ 0.0f }
{

}

void CameraComponent::Update()
{
	mView = glm::mat4{ 1.0f };

	mCameraPos = mOwner->GetPosition();
	//mCameraTarget = mCameraPos + mOwner->GetForward();
	mCameraTarget = mCameraPos + mForward;

	mView = glm::lookAt(mCameraPos, mCameraTarget, mCameraUp);
}

void CameraComponent::ProcessInput(bool* keyState, int x, int y)
{
	auto rot = mOwner->GetRotation();
	rot += -x / mSensitivity;
	mOwner->SetRotation(rot);

	mPitch += y / mSensitivity;
	mPitch = glm::clamp(mPitch, -89.0f, 89.0f);

	mForward = glm::rotateX(glm::normalize(mOwner->GetForward()), glm::radians(mPitch));
}