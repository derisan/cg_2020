#pragma once
#include "object.h"
class Plane :
    public Object
{
public:
    Plane();
    ~Plane();

    void Update() override;
    void Draw(class Shader* shader);
    void Load();

private:
    class VertexArray* mVertexArray;
};

