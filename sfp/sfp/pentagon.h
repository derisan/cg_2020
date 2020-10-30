#pragma once
#include "object.h"
class Pentagon :
    public Object
{
public:
    enum PointIdx
    {
        kTwelve,
        kNine,
        kSeven,
        kFive,
        kThree
    };

    Pentagon(const glm::vec2& twelve, const glm::vec2& nine,
        const glm::vec2& seven, const glm::vec2& five, const glm::vec2& three, class ObjectManager* manager);
    ~Pentagon();

    void Update() override;
    void Draw() override;
    void Load() override;

    void UpdateSide();

    const std::vector<Side>& GetSides() const override { return mSides; }
    const std::vector<glm::vec2>& GetPoints() const override { return mPoints; }
private:
    glm::vec2 mTwelvePoint;
    glm::vec2 mNinePoint;
    glm::vec2 mSevenPoint;
    glm::vec2 mFivePoint;
    glm::vec2 mThreePoint;

    std::vector<Side> mSides;
    std::vector<glm::vec2> mPoints;

    class VertexArray* mVertexArray;
};

