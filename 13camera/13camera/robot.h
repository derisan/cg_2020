#pragma once
#include "actor.h"
class Robot :
    public Actor
{
public:
    Robot(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kRobot);

    void UpdateActor() override;

    void ChangeDirection(bool reflect = false);
    bool IsNear();

private:
    class BoxComponent* mBox;
    Actor* mTarget;
    
    struct Border
    {
        glm::vec2 x;
        glm::vec2 z;
    };
    Border mBorder;
    
    float mRotationCooldown;
    float mAngle;
    
    const float kMovementSpeed{ 1.0f };
    const float kRotationSpeed{ 100.0f };
};

