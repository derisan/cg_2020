#pragma once

#include "actor.h"

class FpsActor:
    public Actor
{
public:
    FpsActor(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kDefault);

    void UpdateActor() override;
    void ActorInput(bool* keyState, int x, int y) override;

    // Getters
    const glm::mat4& GetView() const { return mView; }

private:
    float mForwardSpeed;
    float mStrafeSpeed;
    float mPitch;
    const float kSpeed{ 5.0f };
    const float kSensitivty{ 3.0f };

    glm::mat4 mView;
};

