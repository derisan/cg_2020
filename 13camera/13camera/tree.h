#pragma once
#include "actor.h"
class Tree:
    public Actor
{
public:
    Tree(Gfw* gfw, Gfw::Layer layer = Gfw::Layer::kObstacle);

    // Getters
    class BoxComponent* GetBox() { return mBox; }

private:
    class BoxComponent* mBox;
};

