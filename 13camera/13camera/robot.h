#pragma once
#include "actor.h"
class Robot :
    public Actor
{
public:
    Robot(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kRobot);

    void UpdateActor() override;

private:
    class BoxComponent* mBox;
};

