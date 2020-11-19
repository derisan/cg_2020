#pragma once
#include "actor.h"
class Robot :
    public Actor
{
public:
    Robot(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kRobot);

    void UpdateActor() override;

    void ChangeDirection(bool reflect = false);

private:
    class BoxComponent* mBox;

    struct Border
    {
        glm::vec2 x;
        glm::vec2 z;
    };
    Border mBorder;

    float mRotationCooldown;
    const float kMovementSpeed{ 5.0f };
};

