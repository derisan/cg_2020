#pragma once
#include "actor.h"
class Snowman :
    public Actor
{
public:
    Snowman(class Game* game);

    void Draw(class Shader* shader) override;

private:
    class Mesh* mMesh;
};

