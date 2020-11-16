#pragma once

#include "component.h"

#include <glm/glm.hpp>

class CameraComponent:
    public Component
{
public:
    CameraComponent(class Actor* owner);

    void Update() override;
    void ProcessInput(bool* keyState, int x, int y) override;

    // Getters
    const glm::mat4 GetView() const { return mView; }

private:
    glm::vec3 mCameraPos;
    glm::vec3 mCameraTarget;
    glm::vec3 mCameraUp;

    glm::mat4 mView;

    float mSensitivity;
};

