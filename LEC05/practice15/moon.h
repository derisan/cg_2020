#pragma once
#include "planet.h"
class Moon :
    public Planet
{
public:
    Moon(class Earth* owner);

    void Update(float dt) override;
    void Draw(class Shader* shader) override;

private:
    float mSpeed;
    float mAngle;

    class Earth* mOwner;
};

