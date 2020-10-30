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