#include "triangle.h"

#include <GL/glew.h>

#include "object_manager.h"
#include "vertexarray.h"
#include "shader.h"

Triangle::Triangle(const glm::vec2& left, const glm::vec2& right,
	const glm::vec2& mid, ObjectManager* manager)
	: Object{ manager },
	mLeftPoint{ left },
	mRightPoint{ right },
	mMidPoint{ mid },
	mLeftSide{ left, mid },
	mRightSide{ right, mid },
	mMidSide{ left, right },
	mVertexArray{ nullptr }
{
	mSides.emplace_back(mLeftSide);
	mSides.emplace_back(mRightSide);
	mSides.emplace_back(mMidSide);
	Load();
}

Triangle::~Triangle()
{
	delete mVertexArray;
}

void Triangle::Update()
{
	Object::Update();

	auto speed = GetXSpeed();
	mLeftPoint.x += speed;
	mRightPoint.x += speed;
	mMidPoint.x += speed;

	speed = GetYSpeed();
	mLeftPoint.y += speed;
	mRightPoint.y += speed;
	mMidPoint.y += speed;

	if (mLeftPoint.x < -1.3f || mRightPoint.x > 1.3f)
		SetState(State::kDead);

	UpdateSide();
	Load();
}

void Triangle::Draw()
{
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(),
		GL_UNSIGNED_INT, nullptr);
}

void Triangle::Load()
{
	const float vertices[] = {
		mLeftPoint.x, mLeftPoint.y,
		mRightPoint.x, mRightPoint.y,
		mMidPoint.x, mMidPoint.y
	};

	const unsigned int indices[] = {
		0, 1, 2,
	};

	if (mVertexArray)
		delete mVertexArray;
	mVertexArray = new VertexArray(vertices, static_cast < unsigned int>(sizeof(vertices) / sizeof(float)),
		indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
}

void Triangle::UpdateSide()
{
	mLeftSide = { mLeftPoint, mMidPoint };
	mRightSide = { mRightPoint, mMidPoint };
	mMidSide = { mLeftPoint, mRightPoint };

	mSides.clear();
	mSides.emplace_back(mLeftSide);
	mSides.emplace_back(mRightSide);
	mSides.emplace_back(mMidSide);
}