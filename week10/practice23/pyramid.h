#pragma once

#include "actor.h"

class Pyramid:
    public Actor
{
public:
    enum class Type
    {
        kBottom,
        kLeft,
        kRight,
        kFront,
        kBack
    };

    Pyramid(class Game* game, Type type);

    void ActorInput(unsigned char key) override;
    void UpdateActor() override;
    void Draw(class Shader* shader) override;

    void Load();

private:
    class Texture* mTexture;
    class VertexArray* mVertexArray;

    Type mType;

    float mRotationSpeed;
};

