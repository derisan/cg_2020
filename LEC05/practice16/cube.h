#pragma once
#include "object.h"
class Cube :
    public Object
{
public:
    Cube();
    ~Cube();

    void Draw(class Shader* shader) override;
    void Load() override;
private:
    class VertexArray* mVertexArray;
};

