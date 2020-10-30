#include "triangle.h"

#include <GL/glew.h>

#include "object_manager.h"
#include "vertexarray.h"


Triangle::Triangle(const glm::vec2& left, const glm::vec2& right,
	const glm::vec2& mid, ObjectManager* manager)
	: Object{ manager },
	mLeftPoint{ left },
	mRightPoint{ right },
	mMidPoint{ mid },
	mVertexArray{ nullptr }
{
	SetType(Type::kTriangle);

	mPoints.emplace_back(mLeftPoint);
	mPoints.emplace_back(mRightPoint);
	mPoints.emplace_back(mMidPoint);

	mSides.emplace_back(Side{ left, mid });
	mSides.emplace_back(Side{ right, mid });
	mSides.emplace_back(Side{ left, right });
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

	UpdateSide();
	Load();

	if (mLeftPoint.x < -1.3f || mRightPoint.x > 1.3f
		|| mLeftPoint.y < -1.3f)
		SetState(State::kDead);
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
	mPoints.clear();
	mPoints.emplace_back(mLeftPoint);
	mPoints.emplace_back(mRightPoint);
	mPoints.emplace_back(mMidPoint);

	mSides.clear();
	mSides.emplace_back(Side{ mLeftPoint, mMidPoint });
	mSides.emplace_back(Side{ mRightPoint, mMidPoint });
	mSides.emplace_back(Side{ mLeftPoint, mRightPoint });
}