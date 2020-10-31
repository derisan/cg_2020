#include "rect.h"

#include <GL/glew.h>

#include "object_manager.h"
#include "vertexarray.h"

Rect::Rect(const glm::vec2& leftTop, const glm::vec2& rightTop,
	const glm::vec2& leftBottom, const glm::vec2& rightBottom, class ObjectManager* manager)
	: Object{ manager },
	mLeftTopPoint{ leftTop },
	mRightTopPoint{ rightTop },
	mLeftBottomPoint{ leftBottom },
	mRightBottomPoint{ rightBottom },
	mVertexArray{ nullptr }
{
	SetType(Type::kRect);

	UpdateSide();
	Load();
}

Rect::~Rect()
{
	delete mVertexArray;
}

void Rect::Update()
{
	if (GetState() == State::kActive)
	{
		Object::Update();

		auto speed = GetXSpeed();
		mLeftTopPoint.x += speed;
		mRightTopPoint.x += speed;
		mLeftBottomPoint.x += speed;
		mRightBottomPoint.x += speed;

		speed = GetYSpeed();
		mLeftTopPoint.y += speed;
		mRightTopPoint.y += speed;
		mLeftBottomPoint.y += speed;
		mRightBottomPoint.y += speed;

		UpdateSide();
		Load();

		if (mLeftTopPoint.x < -1.3f || mLeftBottomPoint.x < -1.3f || mRightTopPoint.x > 1.3f || mRightBottomPoint.x > 1.3f
			|| mLeftBottomPoint.y < -1.3f)
			SetState(State::kDead);
	}
}

void Rect::Draw()
{
	mVertexArray->SetActive();
	glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(),
		GL_UNSIGNED_INT, nullptr);
}

void Rect::Load()
{
	const float vertices[] = {
	mLeftTopPoint.x, mLeftTopPoint.y,
	mRightTopPoint.x, mRightTopPoint.y,
	mRightBottomPoint.x , mRightBottomPoint.y,
	mLeftBottomPoint.x, mLeftBottomPoint.y
	};

	const unsigned int indices[] = {
		0, 2, 1,
		0, 3, 2
	};

	if (mVertexArray)
		delete mVertexArray;
	mVertexArray = new VertexArray(vertices, static_cast <unsigned int>(sizeof(vertices) / sizeof(float)),
		indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
}

void Rect::UpdateSide()
{
	mPoints.clear();
	mPoints.emplace_back(mLeftTopPoint);
	mPoints.emplace_back(mRightTopPoint);
	mPoints.emplace_back(mLeftBottomPoint);
	mPoints.emplace_back(mRightBottomPoint);

	mSides.clear();
	mSides.emplace_back(Side{ mLeftTopPoint, mRightTopPoint});
	mSides.emplace_back(Side{ mRightTopPoint, mRightBottomPoint});
	mSides.emplace_back(Side{ mRightBottomPoint, mLeftBottomPoint });
	mSides.emplace_back(Side{ mLeftBottomPoint, mLeftTopPoint });
}

const glm::vec2 Rect::GetCenter() const
{
	return glm::vec2{
		(mLeftTopPoint.x + mRightTopPoint.x + mLeftBottomPoint.x + mRightBottomPoint.x) / 4,
		(mLeftTopPoint.y + mRightTopPoint.y + mLeftBottomPoint.y + mRightBottomPoint.y) / 4
	};
}

void Rect::Rearrange(const glm::vec2& center)
{
	glm::vec2 prevCenter = GetCenter();
	glm::vec2 leftTopCen = mLeftTopPoint - prevCenter;
	glm::vec2 rightTopCen = mRightTopPoint - prevCenter;
	glm::vec2 leftBottomCen = mLeftBottomPoint - prevCenter;
	glm::vec2 rightBottomCen = mRightBottomPoint - prevCenter;

	mLeftTopPoint = leftTopCen + center;
	mRightTopPoint = rightTopCen + center;
	mLeftBottomPoint = leftBottomCen + center;
	mRightBottomPoint = rightBottomCen + center;

	Load();
}