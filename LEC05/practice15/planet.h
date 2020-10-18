#pragma once
#include "object.h"

class Planet :
    public Object
{
public:
    Planet();
    ~Planet();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;
    
    class VertexArray* GetVertexArray() { return mVertexArray; }

private:
    class VertexArray* mVertexArray;
};

