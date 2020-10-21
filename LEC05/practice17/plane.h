#pragma once
#include "object.h"
class Plane :
    public Object
{
public:
    enum Color
    {
        kRed,
        kGreen,
        kBlue,
        kYellow,
        kMagenta,
        kCyan,
        kBlack
    };

    Plane(Color color = kBlack);
    ~Plane();

    virtual void Draw(class Shader* shader) override;
    virtual void Load() override;
    
    const glm::vec3& GetColor() const { return mColor; }
private:
    class VertexArray* mVertexArray;
    glm::vec3 mColor;
};

