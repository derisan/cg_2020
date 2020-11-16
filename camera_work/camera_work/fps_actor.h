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
    class CameraComponent* GetCamera() { return mCamera; }

private:
    float mForwardSpeed;
    float mStrafeSpeed;
    const float kSpeed{ 5.0f };

    class CameraComponent* mCamera;
};

