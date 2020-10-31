#include "net.h"

#include <iostream>

#include "game.h"
#include "line.h"
#include "triangle.h"
#include "rect.h"
#include "pentagon.h"

Net::Net(int w, int h, Game* game)
	: mGame{ game },
	mScrWidth{ w },
	mScrHeight{ h },
	mBorder{ -0.55f },
	mObjCount{ 0 }
{
	MakeMesh();
}

Net::~Net()
{
	for (auto line : mLines)
		delete line;
	mLines.clear();
}

void Net::Update(std::vector<Object*>& objs)
{
	CheckCollision(objs);
}

void Net::Draw()
{
	for (auto line : mLines)
		line->Draw();
}

void Net::CheckCollision(std::vector<Object*>& objs)
{
	if (mObjCount > 24)
		return;

	for (auto obj : objs)
	{
		if (obj->GetState() != Object::State::kActive)
			continue;

		auto type = obj->GetType();
		if (type == Object::Type::kTriangle)
		{
			auto points = obj->GetPoints();
			if (points[Triangle::kMid].y < mBorder)
			{
				obj->SetState(Object::State::kPaused);
				Reposition(obj);
			}
		}

		else if (type == Object::Type::kRect)
		{
			auto points = obj->GetPoints();
			if (points[Rect::kLeftBottomPoint].y < mBorder)
			{
				obj->SetState(Object::State::kPaused);
				Reposition(obj);
			}
		}

		else if (type == Object::Type::kPentagon)
		{
			auto points = obj->GetPoints();
			if (points[Pentagon::kSeven].y < mBorder)
			{
				obj->SetState(Object::State::kPaused);
				Reposition(obj);
			}
		}
	}
}

void Net::Reposition(Object* obj)
{
	glm::vec2 center{ -0.875f + 0.25f * (mObjCount % 8), -0.925f + 0.15f * (mObjCount / 8) };
	obj->Rearrange(center);
		
	++mObjCount;
}

void Net::MakeMesh()
{
	// Rows
	mLines.emplace_back(new Line{ glm::vec2{-1.0f, -0.85f}, glm::vec2{1.0f, -0.85f} });
	mLines.emplace_back(new Line{ glm::vec2{-1.0f, -0.7f}, glm::vec2{1.0f, -0.7f} });
	mLines.emplace_back(new Line{ glm::vec2{-1.0f, -0.55f}, glm::vec2{1.0f, -0.55f} });

	// Columns
	mLines.emplace_back(new Line{ glm::vec2{-0.75f, -0.55f}, glm::vec2{-0.75f, -1.0f} });
	mLines.emplace_back(new Line{ glm::vec2{-0.5f, -0.55f}, glm::vec2{-0.5f, -1.0f} });
	mLines.emplace_back(new Line{ glm::vec2{-0.25f, -0.55f}, glm::vec2{-0.25f, -1.0f} });
	mLines.emplace_back(new Line{ glm::vec2{0.0f, -0.55f}, glm::vec2{0.0f, -1.0f} });
	mLines.emplace_back(new Line{ glm::vec2{0.25f, -0.55f}, glm::vec2{0.25f, -1.0f} });
	mLines.emplace_back(new Line{ glm::vec2{0.5f, -0.55f}, glm::vec2{0.5f, -1.0f} });
	mLines.emplace_back(new Line{ glm::vec2{0.75f, -0.55f}, glm::vec2{0.75f, -1.0f} });
}