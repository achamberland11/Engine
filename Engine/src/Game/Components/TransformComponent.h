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
    
    bool CanDuplicate() const override { return bCanDuplicate; }
    bool CanBeDisabled() const override { return bCanBeDisabled; }
    bool CanBeDeleted() const override { return bCanBeDeleted; }
    
    Vector3 Position = {0,0,0};
    Vector3 Rotation = {0,0,0};
    Vector3 Scale = {1,1,1};
};
