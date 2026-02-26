#pragma once
#include "../Component.h"
#include "../../Utils/Math.h"

class CTransformComponent : public CComponent
{
public:
    GENERATE_REFLECTION()
    
    CTransformComponent()
    {
        Name = "Transform";
        bEnabled = true;
        bCanBeDisabled = false;
    }
    
    Vector3 Position = {0.0f, 0.0f, 0.0f};
    Vector3 Rotation = {0.0f, 0.0f, 0.0f};
    Vector3 Scale = {1.0f, 1.0f, 1.0f};
};
