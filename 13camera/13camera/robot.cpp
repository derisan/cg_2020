#include "robot.h"

#include <glm/gtx/norm.hpp>

#include "mesh_component.h"
#include "box_component.h"
#include "mesh.h"
#include "random.h"


Robot::Robot(Gfw* gfw, Gfw::Layer layer)
	: Actor{ gfw, layer },
	mBox{ nullptr },
	mTarget{ nullptr },
	mBorder{ {-13.f, 13.f}, {-19.f, 1.f} },
	mRotationCooldown{ 0.f },
	mAngle{ 0.0f },
	mMovementSpeed{ 3.0f }
{
	auto mc = new MeshComponent{ this, "Assets/robot.gpmesh" };
	mBox = new BoxComponent{ this };
	mBox->SetObjectBox(mc->GetMesh()->GetBox());

	SetScale(0.1f);

	const auto& player = mGfw->GetActorsAt(Gfw::Layer::kPlayer)[0];
	mTarget = player;
}

void Robot::UpdateActor()
{
	mRotationCooldown -= mGfw->dt;

	if (IsNear())
	{
		mMovementSpeed = 0.0f;

		const auto& forward = glm::normalize(GetForward());
		const auto& toA = glm::normalize(mTarget->GetPosition() - GetPosition());

		auto cost = glm::dot(forward, toA);
		auto rot = glm::degrees(glm::acos(cost));
		
		if (rot < 5.0f)
			mMovementSpeed = 3.0f;

		mAngle -= rot * mGfw->dt;

		SetRotation(mAngle);
	}
	else if(mRotationCooldown < 0)
	{
		mMovementSpeed = 3.0f;
		mRotationCooldown = Random::GetFloatRange(1.0f, 2.0f);
		ChangeDirection();
	}

	auto pos = GetPosition();
	auto movement = GetForward() * mMovementSpeed * mGfw->dt;
	pos += movement;

	if (pos.x < mBorder.x.x)
	{
		pos += glm::vec3{ 0.5f, 0.0f, 0.0f };
		ChangeDirection(true);
	}
	else if (pos.x > mBorder.x.y)
	{
		pos -= glm::vec3{ 0.5f, 0.0f, 0.0f };
		ChangeDirection(true);
	}

	if (pos.z < mBorder.z.x)
	{
		pos += glm::vec3{ 0.0f, 0.0f, 0.5f };
		ChangeDirection(true);
	}
	else if (pos.z > mBorder.z.y)
	{
		pos -= glm::vec3{ 0.0f, 0.0f, 0.5f };
		ChangeDirection(true);
	}

	SetPosition(pos);
}

void Robot::ChangeDirection(bool reflect)
{
	if (!reflect)
	{
		auto rot = Random::GetFloatRange(0.f, 360.f);
		SetRotation(rot);
	}
	else
	{
		auto rot = GetRotation() + 180.f;
		SetRotation(rot);
	}
}

bool Robot::IsNear()
{
	const auto& myPos = GetPosition();
	const auto& targetPos = mTarget->GetPosition();

	if (glm::distance2(myPos, targetPos) < 49.0f)
		return true;
	return false;
}