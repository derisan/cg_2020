#pragma once
#include "object.h"
class Plane :
    public Object
{
public:
    Plane(Color color = Color::kBlack);
    ~Plane();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;
    
private:
    class VertexArray* mVertexArray;
};

