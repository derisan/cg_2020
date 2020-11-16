#pragma once

#include "actor.h"

class FpsActor:
    public Actor
{
public:
    FpsActor(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kDefault);

    void UpdateActor() override;
    void ActorInput(unsigned char key) override;

    // Getters
    const glm::mat4& GetView() const { return mView; }

private:
    float mForwardSpeed;
    float mStrafeSpeed;
    const float kSpeed{ 5.0f };

    glm::mat4 mView;
};

