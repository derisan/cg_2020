#pragma once
#include "object.h"
class Orbit :
    public Object
{
public:
    Orbit();
    ~Orbit();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;

    void SetRadius(float radius) { mRadius = radius; }
private:
    class VertexArray* mVertexArray;
    float mRadius;
};

