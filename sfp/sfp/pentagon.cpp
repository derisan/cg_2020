#include "pentagon.h"

#include <GL/glew.h>

#include "object_manager.h"
#include "vertexarray.h"

Pentagon::Pentagon(const glm::vec2& twelve, const glm::vec2& nine,
    const glm::vec2& seven, const glm::vec2& five, const glm::vec2& three, ObjectManager* manager)
    : Object{ manager },
    mTwelvePoint{ twelve },
    mNinePoint{ nine },
    mSevenPoint{ seven },
    mFivePoint{ five },
    mThreePoint{ three },
    mVertexArray{ nullptr }
{
    SetType(Type::kPentagon);

    UpdateSide();
    Load();
}

Pentagon::~Pentagon()
{
    delete mVertexArray;
}

void Pentagon::Update()
{
    if (GetState() == State::kActive)
    {
        Object::Update();

        auto speed = GetXSpeed();
        mTwelvePoint.x += speed;
        mNinePoint.x += speed;
        mSevenPoint.x += speed;
        mFivePoint.x += speed;
        mThreePoint.x += speed;

        speed = GetYSpeed();
        mTwelvePoint.y += speed;
        mNinePoint.y += speed;
        mSevenPoint.y += speed;
        mFivePoint.y += speed;
        mThreePoint.y += speed;

        UpdateSide();
        Load();

        if (mNinePoint.x < -1.3f || mThreePoint.x > 1.3f || mSevenPoint.y < -1.3f)
            SetState(State::kDead);
    }
}

void Pentagon::Draw()
{
    mVertexArray->SetActive();
    glDrawElements(GL_TRIANGLES, mVertexArray->GetNumIndices(),
        GL_UNSIGNED_INT, nullptr);
}

void Pentagon::Load()
{
    const float vertices[] = {
	mTwelvePoint.x, mTwelvePoint.y,
    mNinePoint.x, mNinePoint.y,
    mSevenPoint.x, mSevenPoint.y,
    mFivePoint.x, mFivePoint.y,
    mThreePoint.x, mThreePoint.y
    };

    const unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4
    };

    if (mVertexArray)
        delete mVertexArray;
    mVertexArray = new VertexArray(vertices, static_cast <unsigned int>(sizeof(vertices) / sizeof(float)),
        indices, static_cast<unsigned int>(sizeof(indices) / sizeof(unsigned int)));
}

void Pentagon::UpdateSide()
{
    mPoints.clear();
    mPoints.emplace_back(mTwelvePoint);
    mPoints.emplace_back(mNinePoint);
    mPoints.emplace_back(mSevenPoint);
    mPoints.emplace_back(mFivePoint);
    mPoints.emplace_back(mThreePoint);
}

const glm::vec2 Pentagon::GetCenter() const
{
    return glm::vec2{
        (mTwelvePoint.x + mNinePoint.x + mSevenPoint.x + mFivePoint.x + mThreePoint.x) / 5,
        (mTwelvePoint.y + mNinePoint.y + mSevenPoint.y + mFivePoint.y + mThreePoint.y) / 5
    };
}

void Pentagon::Rearrange(const glm::vec2& center)
{
    glm::vec2 prevCenter = GetCenter();
    
    glm::vec2 twelveCen = mTwelvePoint - prevCenter;
    glm::vec2 nineCen = mNinePoint - prevCenter;
    glm::vec2 sevenCen = mSevenPoint - prevCenter;
    glm::vec2 fiveCen = mFivePoint - prevCenter;
    glm::vec2 threeCen = mThreePoint - prevCenter;

    mTwelvePoint = twelveCen + center;
    mNinePoint = nineCen + center;
    mSevenPoint = sevenCen + center;
    mFivePoint = fiveCen + center;
    mThreePoint = threeCen + center;

    Load();
}