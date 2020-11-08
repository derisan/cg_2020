#pragma once
#include "actor.h"
class Cube :
    public Actor
{
public:
    Cube(class Game* game);

    void Draw(class Shader* shader) override;
private:
    class Mesh* mMesh;
    class Shader* mShader;
};

