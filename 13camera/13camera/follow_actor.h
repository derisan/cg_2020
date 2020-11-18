#pragma once
#include "actor.h"
class FollowActor:
    public Actor
{
public:
    FollowActor(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kDefault);

    void UpdateActor() override;
    void ActorInput(bool* keyState, int x, int y) override;

    // Getters
    const glm::mat4& GetView() const { return mView; }

private:
    float mForwardSpeed;
    float mRotationSpeed;
    const float kMovementSpeed{ 5.0f };
    const float kRotationSpeed{ 100.0f };

    glm::mat4 mView;
};

