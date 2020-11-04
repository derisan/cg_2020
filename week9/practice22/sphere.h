#pragma once
#include "object.h"
class Sphere :
    public Object
{
public:
    Sphere();
    ~Sphere();

    void Update() override;
    void Draw(class Shader* shader);
    void Load();

private:
    class VertexArray* mVertexArray;

    float mAngle;
    const float dt{ 16.0f / 1000.0f };
};

