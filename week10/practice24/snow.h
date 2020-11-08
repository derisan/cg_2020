#pragma once

#include "actor.h"

class Snow :
    public Actor
{
public:
    Snow(class Game* game);

    void UpdateActor() override;
    void Draw(class Shader* shader) override;

private:
    class Mesh* mMesh;

    glm::vec3 mVelocity;
    const glm::vec3 mGravity;
};

