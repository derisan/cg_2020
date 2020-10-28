#pragma once
#include "object.h"
class Cube :
    public Object
{
public:
    enum Part
    {
        kHead,
        kNose,
        kBody,
        kLeftArm,
        kRightArm,
        kLeftLeg,
        kRightLeg,
        kDefault
    };

    Cube(Part part = Part::kDefault, Color color = Color::kBlack);
    ~Cube();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;

    void DefaultLoad();
    void HeadLoad();
    void NoseLoad();
    void BodyLoad();
    void LeftArmLoad();
    void RightArmLoad();
    void LeftLegLoad();
    void RightLegLoad();

    Part GetPart() const { return mPart; }

private:
    class VertexArray* mVertexArray;
    Part mPart;
};

