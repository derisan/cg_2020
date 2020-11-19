#pragma once
#include "actor.h"
class Player :
    public Actor
{
public:
    enum ViewOption
    {
        kFollow,
        kFPS
    };

    Player(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kPlayer);

    void UpdateActor() override;
    void ActorInput(bool* keyState, int x, int y) override;

    // Getters
    const glm::mat4& GetView() const { return mView; }
    
    // Setters
    void SetView(const glm::mat4& view) { mView = view; }
    void SetViewOption(ViewOption opt) { mViewOption = opt; }

private:
    float mForwardSpeed;
    float mRotationSpeed;
    float mStrafeSpeed;
    
    const float kSensitivty{ 3.0f };
    const float kMovementSpeed{ 5.0f };
    const float kRotationSpeed{ 100.0f };

    ViewOption mViewOption;

    glm::mat4 mView;
};

