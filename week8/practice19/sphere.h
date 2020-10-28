#pragma once
#include "object.h"
class Sphere :
    public Object
{
public:
    Sphere(Color color = Object::kBlack);
    ~Sphere();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;


private:
    class VertexArray* mVertexArray;
};

