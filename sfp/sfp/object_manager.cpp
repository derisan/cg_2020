#include "object_manager.h"

#include <iostream>
#include <algorithm>

#include "game.h"
#include "random.h"
#include "triangle.h"
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
			delete mPaths.front();
			mPaths.erase(std::begin(mPaths));
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
	//std::cout << p1.x << ", " << p1.y << std::endl;
	//std::cout << p2.x << ", " << p2.y << std::endl;
	//std::cout << s1.p1.x << ", " << s1.p1.y << std::endl;
	//std::cout << s1.p2.x << ", " << s1.p2.y << std::endl;

	// 객체의 세 점의 정보 가져오기
	// 매개변수 s1과 s2가 왼,오,중변인지 확인하기
	// s1과 s2에 따라 새로운 도형을 만들고 기존 객체는 삭제.
}