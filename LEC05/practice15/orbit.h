#pragma once
#include "object.h"
class Orbit :
    public Object
{
public:
    Orbit();
    ~Orbit();

    void Draw(class Shader* shader) override;
    void Load() override;

private:
    class VertexArray* mVertexArray;
};

