#include "object_manager.h"

#include <iostream>
#include <algorithm>

#include "game.h"
#include "random.h"
#include "triangle.h"
#include "rect.h"
#include "line.h"
#include "utils.h"

ObjectManager::ObjectManager(Game* game)
	: mCooldown{ 2.0f },
	mShouldDrawPath{ true },
	mGame{ game }
{

}

ObjectManager::~ObjectManager()
{
	while (!mObjs.empty())
		delete mObjs.back();
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
	auto choice = Random::GetIntRange(0, 1);
	
	glm::vec2 p1 = { -1.0f, Random::GetFloatRange(0.0f, 0.8f) };
	glm::vec2 p2 = { 1.0f, Random::GetFloatRange(0.0f, 0.8f) };
	CreatePath(p1, p2);
	
	float xSpeed{ 0.005f };
	float ySpeed = (p2.y - p1.y) / 400.0f;

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

	// s1과 s2가 왼,오,중변인지 확인하기
	
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
	auto sides = obj->GetSides();
	int option{ 0 };
	if (s1.p1 == sides[Triangle::kLeft].p1 && s1.p2 == sides[Triangle::kLeft].p2)
	{
		if (s2.p1 == sides[Triangle::kRight].p1 && s2.p2 == sides[Triangle::kRight].p2)		// 좌우
			option = 0;
		else if (s2.p1 == sides[Triangle::kMid].p1 && s2.p2 == sides[Triangle::kMid].p2)	// 좌중
			option = 1;
	}
	else if (s1.p1 == sides[Triangle::kRight].p1 && s1.p2 == sides[Triangle::kRight].p2)
		if (s2.p1 == sides[Triangle::kMid].p1 && s2.p2 == sides[Triangle::kMid].p2)		// 우중
			option = 2;

	return option;
}

int ObjectManager::GetRectDivideOption(const Object::Side& s1, const Object::Side& s2, Object* obj)
{
	// 상우하좌(반시계)
	auto sides = obj->GetSides();
	int option{ 0 };
	if (s1.p1 == sides[Rect::kTopSide].p1 && s1.p2 == sides[Rect::kTopSide].p2)
	{
		if (s2.p1 == sides[Rect::kLeftSide].p1 && s2.p2 == sides[Rect::kLeftSide].p2) /* 상좌 */
			option = 0;
		else if (s2.p1 == sides[Rect::kBottomSide].p1 && s2.p2 == sides[Rect::kBottomSide].p2) /* 상하 */
			option = 1;
		else if (s2.p1 == sides[Rect::kRightSide].p1 && s2.p2 == sides[Rect::kRightSide].p2) /* 상우 */
			option = 2;
	}
	else if (s1.p1 == sides[Rect::kRightSide].p1 && s1.p2 == sides[Rect::kRightSide].p2)
	{
		if (s2.p1 == sides[Rect::kLeftSide].p1 && s2.p2 == sides[Rect::kLeftSide].p2) /* 좌우 */
			option = 3;
		else if (s2.p1 == sides[Rect::kBottomSide].p1 && s2.p2 == sides[Rect::kBottomSide].p2) /* 우하 */
			option = 4;
	}
	else if (s1.p1 == sides[Rect::kBottomSide].p1 && s1.p2 == sides[Rect::kBottomSide].p2)
	{
		if (s2.p1 == sides[Rect::kLeftSide].p1 && s2.p2 == sides[Rect::kLeftSide].p2) /* 좌하 */
			option = 5;
	}
	return option;
}

void ObjectManager::DivideTriangleIntoTwo(const glm::vec2& p1, const glm::vec2& p2, int option, Object* obj)
{
	// Index 0 : left, 1 : right, 2 : mid
	auto points = obj->GetPoints();

	// 좌우 슬라이스
	if (option == 0)
	{
		auto tri = new Triangle(p1, p2, points[Triangle::kMid], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);

		// 사각형 생성
		auto rect = new Rect(p1, p2, points[Triangle::kLeft], points[Triangle::kRight], this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
	}
	// 좌중 슬라이스
	else if (option == 1)
	{
		auto tri = new Triangle(p1, p2, points[Triangle::kLeft], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);

		auto rect = new Rect(p1, points[Triangle::kMid], p2, points[Triangle::kRight], this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
	}
	// 우중 슬라이스
	else
	{
		auto tri = new Triangle(p1, p2, points[Triangle::kRight], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);

		auto rect = new Rect(points[Triangle::kLeft], points[Triangle::kMid], p2, p1, this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
	}
	
	// 원본 객체 삭제
	obj->SetState(Object::State::kDead);
}

void ObjectManager::DivideRectIntoTwo(const glm::vec2& p1, const glm::vec2& p2, int option, class Object* obj)
{

}