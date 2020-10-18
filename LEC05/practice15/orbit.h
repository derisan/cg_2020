#pragma once
#include "object.h"
class Orbit :
    public Object
{
public:
    Orbit();
    ~Orbit();

    virtual void Update(float dt) override;
    virtual void Draw(class Shader* shader) override;
    void Load() override;

    void SetRadius(float radius) { mRadius = radius; }
    class VertexArray* GetVertexArray() { return mVertexArray; }
private:
    class VertexArray* mVertexArray;
    float mRadius;
};

