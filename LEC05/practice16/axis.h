#pragma once
#include "object.h"
class Axis :
    public Object
{
public:
    Axis();
    ~Axis();

    void Draw(class Shader* shader) override;
    void Load() override;

private:
    class VertexArray* mVertexArray;
};

