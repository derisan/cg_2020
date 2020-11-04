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
};

