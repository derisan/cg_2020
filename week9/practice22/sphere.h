#pragma once
#include "object.h"
class Sphere :
    public Object
{
public:
    Sphere();
    ~Sphere();

    void Update() override;
    void Draw(class Shader* shader);
    void Load();

    bool GetIsSnow() const { return mIsSnow; }
    void SetIsSnow(bool value) { mIsSnow = value; }
    void SetSpeed(float speed) { mSpeed = speed; }
private:
    class VertexArray* mVertexArray;

    float mSpeed;
    const float dt{ 16.0f / 1000.0f };

    bool mIsSnow;
};

