#pragma once
#include "object.h"
class Cube :
    public Object
{
public:
    Cube(Color color = Color::kBlack);
    ~Cube();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;

private:
    class VertexArray* mVertexArray;
};

