#pragma once
#include "plane.h"
class Pyramid :
    public Plane
{
public:
    enum Side
    {
        kFront,
        kLeft,
        kRight,
        kBack
    };

    Pyramid(Side side);

    void Load() override;

    void CreateFront();
    void CreateBack();
    void CreateLeft();
    void CreateRight();
private:
    Side mSide;
};

