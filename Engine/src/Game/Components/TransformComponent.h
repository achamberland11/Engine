#pragma once
#include "../Component.h"
#include "../../Utils/Math.h"

class GTransformComponent : public GComponent
{
public:
    GENERATE_REFLECTION()
    GENERATE_COMPONENT(false, false, false)
    
    GTransformComponent()
    {
        Name = "Transform";
    }
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
    
    Vector3 Position = {0,0,0};
    Vector3 Rotation = {0,0,0};
    Vector3 Scale = {1,1,1};
};
