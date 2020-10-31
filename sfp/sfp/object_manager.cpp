#include "object_manager.h"

#include <iostream>
#include <algorithm>

#include "game.h"
#include "random.h"
#include "triangle.h"
#include "rect.h"
#include "pentagon.h"
#include "line.h"
#include "utils.h"

ObjectManager::ObjectManager(Game* game)
	: mCooldown{ 0.0f },
	mShouldDrawPath{ true },
	mGame{ game }
{

}

ObjectManager::~ObjectManager()
{
	while (!mObjs.empty())
		delete mObjs.back();
	mObjs.clear();

	for (auto path : mPaths)
		delete path;
	mPaths.clear();
}

void ObjectManager::Update()
{
	mCooldown -= dt;
	if (mCooldown < 0)
	{
		mCooldown = 3.0f;
		GenerateRandomPolygon();
	}

	std::vector<Object*> deads;
	for (auto obj : mObjs)
	{
		obj->Update();
		if (obj->GetState() == Object::State::kDead)
		{
			deads.emplace_back(obj);
		}
	}

	for (auto obj : deads)
		delete obj;
	deads.clear();

	// Think about how to delete path appropriately
}

void ObjectManager::Draw()
{
	for (auto obj : mObjs)
		obj->Draw();

	if (mShouldDrawPath)
		for (auto path : mPaths)
			path->Draw();
}

void ObjectManager::AddObj(Object* obj)
{
	mObjs.emplace_back(obj);
}

void ObjectManager::RemoveObj(Object* obj)
{
	auto iter = std::find(std::begin(mObjs), std::end(mObjs), obj);
	if (iter != std::end(mObjs))
	{
		mObjs.erase(iter);
	}
}

void ObjectManager::GenerateRandomPolygon()
{
	glm::vec2 p1 = { -1.0f, Random::GetFloatRange(0.0f, 0.8f) };
	glm::vec2 p2 = { 1.0f, Random::GetFloatRange(0.0f, 0.8f) };
	CreatePath(p1, p2);
	
	float xSpeed{ 0.005f };
	float ySpeed = (p2.y - p1.y) / 400.0f;

	auto choice = Random::GetIntRange(0, 1);
	// Create triangle in left side of window
	if (choice == 0)
	{
		glm::vec2 left{ -1.1f, p1.y - Random::GetFloatRange(0.05f, 0.1f )};
		glm::vec2 right{ -0.9f, p1.y - Random::GetFloatRange(0.05f, 0.1f) };
		glm::vec2 mid{ -1.0f, p1.y + Random::GetFloatRange(0.05f, 0.1f) };

		auto tri = new Triangle{ left, right, mid, this };
		tri->SetXSpeed(xSpeed);
		tri->SetYSpeed(ySpeed);
	}
	else
	{
		glm::vec2 left{ 0.9f, p2.y - Random::GetFloatRange(0.05f, 0.1f) };
		glm::vec2 right{ 1.1f, p2.y - Random::GetFloatRange(0.05f, 0.1f) };
		glm::vec2 mid{ 1.0f, p2.y + Random::GetFloatRange(0.05f, 0.1f) };

		auto tri = new Triangle{ left, right, mid, this };
		tri->SetXSpeed(-xSpeed);
		tri->SetYSpeed(-ySpeed);
	}
}

void ObjectManager::CreatePath(const glm::vec2& p1, const glm::vec2& p2)
{
	mPaths.emplace_back(new Line{ p1, p2 });
}

void ObjectManager::CheckCollision(Line* cutter)
{
	if (cutter == nullptr)
		return;

	glm::vec2 pos{ 0.0f };
	std::vector<glm::vec2> poses;
	std::vector<Object::Side> sides;

	for (auto obj : mObjs)
	{
		poses.clear();
		sides.clear();
		for (const auto& side : obj->GetSides())
		{
			if (IsIntersect(cutter->GetStart(), cutter->GetEnd(), side.p1, side.p2, pos))
			{
				poses.emplace_back(pos);
				sides.emplace_back(side);
			}
		}
		if (poses.size() == 2 && sides.size() == 2)
		{
			mGame->DeleteCutter();
			CheckSide(poses[0], poses[1], sides[0], sides[1], obj);
			break;
		}
	}
}

void ObjectManager::CheckSide(const glm::vec2& p1, const glm::vec2& p2, 
	const Object::Side& s1, const Object::Side& s2, Object* obj)
{
	auto type = obj->GetType();
	if (type == Object::Type::kPentagon)
		return;

	int option{ 0 };
	if (type == Object::Type::kTriangle)
	{
		option = GetTriangleDivideOption(s1, s2, obj);
		DivideTriangleIntoTwo(p1, p2, option, obj);
	}
	else if (type == Object::Type::kRect)
	{
		option = GetRectDivideOption(s1, s2, obj);
		DivideRectIntoTwo(p1, p2, option, obj);
	}
}

int ObjectManager::GetTriangleDivideOption(const Object::Side& s1, const Object::Side& s2, Object* obj)
{
	// Triangle' sides are arranged in order of left, right, mid.
	auto sides = obj->GetSides();
	int option{ 0 };
	if (s1.p1 == sides[Triangle::kLeft].p1 && s1.p2 == sides[Triangle::kLeft].p2)
	{
		if (s2.p1 == sides[Triangle::kRight].p1 && s2.p2 == sides[Triangle::kRight].p2)		// Left - Right
			option = 0;
		else if (s2.p1 == sides[Triangle::kMid].p1 && s2.p2 == sides[Triangle::kMid].p2)	// Left - Mid
			option = 1;
	}
	else if (s1.p1 == sides[Triangle::kRight].p1 && s1.p2 == sides[Triangle::kRight].p2)
		if (s2.p1 == sides[Triangle::kMid].p1 && s2.p2 == sides[Triangle::kMid].p2)		// Right - Mid
			option = 2;

	return option;
}

int ObjectManager::GetRectDivideOption(const Object::Side& s1, const Object::Side& s2, Object* obj)
{
	// Rect' sides are arranged in order of counter clockwise(top side first)
	auto sides = obj->GetSides();
	int option{ 0 };
	if (s1.p1 == sides[Rect::kTopSide].p1 && s1.p2 == sides[Rect::kTopSide].p2)
	{
		if (s2.p1 == sides[Rect::kLeftSide].p1 && s2.p2 == sides[Rect::kLeftSide].p2) // Top - Left
			option = 0;
		else if (s2.p1 == sides[Rect::kBottomSide].p1 && s2.p2 == sides[Rect::kBottomSide].p2) // Top - Bottom
			option = 1;
		else if (s2.p1 == sides[Rect::kRightSide].p1 && s2.p2 == sides[Rect::kRightSide].p2) // Top - Right
			option = 2;
	}
	else if (s1.p1 == sides[Rect::kRightSide].p1 && s1.p2 == sides[Rect::kRightSide].p2)
	{
		if (s2.p1 == sides[Rect::kLeftSide].p1 && s2.p2 == sides[Rect::kLeftSide].p2) // Right - Left
			option = 3;
		else if (s2.p1 == sides[Rect::kBottomSide].p1 && s2.p2 == sides[Rect::kBottomSide].p2) // Right - Bottom
			option = 4;
	}
	else if (s1.p1 == sides[Rect::kBottomSide].p1 && s1.p2 == sides[Rect::kBottomSide].p2)
	{
		if (s2.p1 == sides[Rect::kLeftSide].p1 && s2.p2 == sides[Rect::kLeftSide].p2) // Left - Bottom
			option = 5;
	}
	return option;
}

void ObjectManager::DivideTriangleIntoTwo(const glm::vec2& p1, const glm::vec2& p2, int option, Object* obj)
{
	auto points = obj->GetPoints();

	// Slice left - right
	if (option == 0)
	{
		auto tri = new Triangle(p1, p2, points[Triangle::kMid], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);
		tri->SetShouldGravityWork(true);

		auto rect = new Rect(p1, p2, points[Triangle::kLeft], points[Triangle::kRight], this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
		rect->SetShouldGravityWork(true);
	}
	// Slice left - mid
	else if (option == 1)
	{
		auto tri = new Triangle(p1, p2, points[Triangle::kLeft], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);
		tri->SetShouldGravityWork(true);

		auto rect = new Rect(p1, points[Triangle::kMid], p2, points[Triangle::kRight], this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
		rect->SetShouldGravityWork(true);
	}
	// Slice right - mid
	else
	{
		auto tri = new Triangle(p1, p2, points[Triangle::kRight], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);
		tri->SetShouldGravityWork(true);

		auto rect = new Rect(points[Triangle::kLeft], points[Triangle::kMid], p2, p1, this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
		rect->SetShouldGravityWork(true);
	}
	
	// Delete origin
	obj->SetState(Object::State::kDead);
}

void ObjectManager::DivideRectIntoTwo(const glm::vec2& p1, const glm::vec2& p2, int option, Object* obj)
{
	auto points = obj->GetPoints();

	// Slice top - left
	if (option == 0)
	{
		auto tri = new Triangle(p2, p1, points[Rect::kLeftTopPoint], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.0025f);
		tri->SetShouldGravityWork(true);

		auto penta = new Pentagon(p1, p2, points[Rect::kLeftBottomPoint],
			points[Rect::kRightBottomPoint], points[Rect::kRightTopPoint], this);
		penta->SetYSpeed(-0.00125f);
		penta->SetShouldGravityWork(true);
	}
	// Slice top - bottom
	else if (option == 1)
	{
		auto rect = new Rect(points[Rect::kLeftTopPoint], p1, points[Rect::kLeftBottomPoint], p2, this);
		rect->SetYSpeed(-0.0025f);
		rect->SetShouldGravityWork(true);

		rect = new Rect(p1, points[Rect::kRightTopPoint], p2, points[Rect::kRightBottomPoint], this);
		rect->SetYSpeed(-0.00125f);
		rect->SetShouldGravityWork(true);
	}
	// Slice top - right
	else if (option == 2)
	{
		auto tri = new Triangle(p1, p2, points[Rect::kRightTopPoint], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.0025f);
		tri->SetShouldGravityWork(true);

		auto penta = new Pentagon(p1, points[Rect::kLeftTopPoint], points[Rect::kLeftBottomPoint],
			points[Rect::kRightBottomPoint], p2, this);
		penta->SetYSpeed(-0.00125f);
		penta->SetShouldGravityWork(true);
	}
	// Slice right - left
	else if (option == 3)
	{
		auto rect = new Rect(points[Rect::kLeftTopPoint], points[Rect::kRightTopPoint], 
			p2, p1, this);
		rect->SetYSpeed(-0.0025f);
		rect->SetShouldGravityWork(true);

		rect = new Rect(p2, p1, points[Rect::kLeftBottomPoint], points[Rect::kRightBottomPoint], this);
		rect->SetYSpeed(-0.00125f);
		rect->SetShouldGravityWork(true);
	}
	// Slice right - bottom
	else if (option == 4)
	{
		auto tri = new Triangle(p2, points[Rect::kRightBottomPoint], p1, this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.0025f);
		tri->SetShouldGravityWork(true);

		auto penta = new Pentagon(points[Rect::kLeftTopPoint], points[Rect::kLeftBottomPoint], p2, p1, points[Rect::kRightTopPoint], this);
		penta->SetYSpeed(-0.00125f);
		penta->SetShouldGravityWork(true);
	}
	// Slice left - bottom
	else
	{
		auto tri = new Triangle(points[Rect::kLeftBottomPoint], p1, p2, this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.0025f);
		tri->SetShouldGravityWork(true);

		auto penta = new Pentagon(points[Rect::kRightTopPoint], points[Rect::kLeftTopPoint], p2, p1, points[Rect::kRightBottomPoint], this);
		penta->SetYSpeed(-0.00125f);
		penta->SetShouldGravityWork(true);
	}
	obj->SetState(Object::State::kDead);
}