#pragma once
#include "actor.h"
class Background :
    public Actor
{
public:
    Background(class Game* game);

    void Draw(class Shader* shader) override;

private:
    class Mesh* mMesh;
};

