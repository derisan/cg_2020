#pragma once
#include "planet.h"

class Moon :
    public Planet
{
public:
    Moon();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;

    // Setters
    void SetSpeed(float speed) { mSpeed = speed; }
    void SetRevAxis(const glm::vec3& axis) { mRevAxis = axis; }

private:
    float mSpeed;
    float mAngle;
    glm::vec3 mRevAxis;
};

