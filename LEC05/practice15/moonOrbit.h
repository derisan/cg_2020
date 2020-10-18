#pragma once
#include "orbit.h"
class MoonOrbit :
    public Orbit
{
public:
    MoonOrbit();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    
    // Setters
    void SetSpeed(float speed) { mSpeed = speed; }
    void SetRevAxis(const glm::vec3& axis) { mRevAxis = axis; }
private:
    float mAngle;
    float mSpeed;
    glm::vec3 mRevAxis;
};

