#pragma once
#include "planet.h"

class Earth :
    public Planet
{   
public:
    Earth();

    void Update(float dt) override;
    void Draw(Shader* shader) override;

    void OnUpdateWorldTransform() override;

    const glm::vec3& GetRevAxis() const { return mRevAxis; }
    void SetRevAxis(const glm::vec3& axis) { mRevAxis = axis; }

private:
    float mSpeed;
    float mAngle;
    glm::vec3 mRevAxis;
    glm::vec3 mPrevPosition;

    class Moon* mMoon;
};

