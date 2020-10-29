#pragma once

#include "object.h"

class Triangle :
    public Object
{
public:
    Triangle();
    ~Triangle();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;

private:
    class VertexArray* mVertexArray;
};

