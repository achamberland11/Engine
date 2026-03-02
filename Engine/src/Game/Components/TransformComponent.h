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
    }
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
    
    bool CanDuplicate() const override { return bCanDuplicate; }
    bool CanBeDisabled() const override { return bCanBeDisabled; }
    bool CanBeDeleted() const override { return bCanBeDeleted; }
    
    static constexpr bool bCanDuplicate = false;
    static constexpr bool bCanBeDisabled = false;
    static constexpr bool bCanBeDeleted = false;
    
    Vector3 Position = {0,0,0};
    Vector3 Rotation = {0,0,0};
    Vector3 Scale = {1,1,1};
};
