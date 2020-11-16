#include "camera_component.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "actor.h"

CameraComponent::CameraComponent(Actor* owner)
	: Component{ owner },
	mCameraPos{ 0.0f },
	mCameraTarget{ 0.0f },
	mCameraUp{ 0.0f, 1.0f, 0.0f },
	mView{ 1.0f },
	mSensitivity{ 3.0f }
{

}

void CameraComponent::Update()
{
	mView = glm::mat4{ 1.0f };

	const auto& pos = mOwner->GetPosition();

	mCameraPos = pos + glm::vec3{ 0.0f, 0.5f, -1.0f };
	auto forward = mOwner->GetForward();
	mCameraTarget = pos + forward * 3.0f;

	mView = glm::lookAt(mCameraPos, mCameraTarget, mCameraUp);
}

void CameraComponent::ProcessInput(bool* keyState, int x, int y)
{
	auto rot = mOwner->GetRotation();
	rot += -x / mSensitivity;
	mOwner->SetRotation(rot);
}