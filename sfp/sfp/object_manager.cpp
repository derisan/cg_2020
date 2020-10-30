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
		CreateRandomPolygon();
	}

	std::vector<Object*> deads;
	for (auto obj : mObjs)
	{
		obj->Update();
		if (obj->GetState() == Object::State::kDead)
		{
			deads.emplace_back(obj);
			if (!mPaths.empty())
			{
				delete mPaths.front();
				mPaths.erase(std::begin(mPaths));
			}
		}
	}

	for (auto obj : deads)
		delete obj;
	deads.clear();
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

void ObjectManager::CreateRandomPolygon()
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

void ObjectManager::CollisionCheck(Line* cutter)
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
			DivideIntoTwo(poses[0], poses[1], sides[0], sides[1], obj);
			break;
		}
	}
}

void ObjectManager::DivideIntoTwo(const glm::vec2& p1, const glm::vec2& p2, 
	const Object::Side& s1, const Object::Side& s2, Object* obj)
{
	// s1과 s2가 왼,오,중변인지 확인하기
	auto sides = obj->GetSides();
	int option{ 0 };
	if (s1.p1 == sides[0].p1 && s1.p2 == sides[0].p2)
	{
		if (s2.p1 == sides[1].p1 && s2.p2 == sides[1].p2)
		{
			//std::cout << "좌우" << std::endl;
			option = 0;
		}
		else if (s2.p1 == sides[2].p1 && s2.p2 == sides[2].p2)
		{
			//std::cout << "좌중" << std::endl;
			option = 1;
		}
	}
	else if (s1.p1 == sides[1].p1 && s1.p2 == sides[1].p2)
	{
		if (s2.p1 == sides[2].p1 && s2.p2 == sides[2].p2)
		{
			//std::cout << "우중" << std::endl;
			option = 2;
		}
	}

	// 삼각형의 세 점
	// Index 0 : left, 1 : right, 2 : mid
	auto points = obj->GetPoints();

	// 좌우 슬라이스
	if (option == 0)
	{
		auto tri = new Triangle(p1, p2, points[2], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);

		// 사각형 생성
		auto rect = new Rect(p1, p2, points[0], points[1], this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
	}
	// 좌중 슬라이스
	else if (option == 1)
	{
		auto tri = new Triangle(p1, p2, points[0], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);

		auto rect = new Rect(p1, points[2], p2, points[1], this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
	}
	// 우중 슬라이스
	else
	{
		auto tri = new Triangle(p1, p2, points[1], this);
		tri->SetXSpeed(0.0f);
		tri->SetYSpeed(-0.005f);

		auto rect = new Rect(points[0], points[2], p2, p1, this);
		rect->SetXSpeed(0.0f);
		rect->SetYSpeed(-0.0025f);
	}
	obj->SetState(Object::State::kDead);
}