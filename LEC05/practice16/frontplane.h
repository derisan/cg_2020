#pragma once
#include "plane.h"

class FrontPlane :
    public Plane
{
public:
    FrontPlane(Color color);

    virtual void Load() override;
};

