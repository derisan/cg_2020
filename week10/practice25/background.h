#pragma once
#include "actor.h"
class Background :
    public Actor
{
public:
    Background(class Game* game);

    void Draw(class Shader* shader) override;
    void Load();
private:
    class Texture* mTexture;
    class VertexArray* mVertexArray;
};

