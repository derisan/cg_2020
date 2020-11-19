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
	mRotationCooldown{ 0.f }
{
	auto mc = new MeshComponent{ this, "Assets/robot.gpmesh" };
	mBox = new BoxComponent{ this };
	mBox->SetObjectBox(mc->GetMesh()->GetBox());

	SetScale(0.1f);
}

void Robot::UpdateActor()
{
	mRotationCooldown -= mGfw->dt;

	SearchPlayer();

	if (mRotationCooldown < 0 && nullptr == mTarget)
	{
		mRotationCooldown = Random::GetFloatRange(1.0f, 2.0f);
		ChangeDirection();
	}
	else if (mTarget)
	{

	}

	auto pos = GetPosition();
	auto movement = GetForward() * kMovementSpeed * mGfw->dt;
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

void Robot::SearchPlayer()
{
	const auto& players = mGfw->GetActorsAt(Gfw::Layer::kPlayer);

	for (auto player : players)
	{
		const auto& pPos = player->GetPosition();
		const auto& myPos = GetPosition();

		if (glm::distance2(pPos, myPos) < 36.0f)
		{
			mTarget = player;
			return;
		}
	}
	mTarget = nullptr;
}