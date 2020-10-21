#pragma once
#include "object.h"
class Axis :
    public Object
{
public:
    Axis(Color color = kBlack);
    ~Axis();

    void Draw(class Shader* shader) override;
    void Load() override;

private:
    class VertexArray* mVertexArray;
};

