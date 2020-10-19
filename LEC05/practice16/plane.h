#pragma once
#include "object.h"
class Plane :
    public Object
{
public:
    Plane();
    ~Plane();

    void Draw(class Shader* shader) override;
    void Load() override;

private:
    class VertexArray* mVertexArray;
};

