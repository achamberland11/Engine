#pragma once
#include "../Component.h"
#include "../../Utils/Math.h"

class CTransformComponent : public CComponent
{
public:
    GENERATE_REFLECTION()
    
    static constexpr bool bCanDuplicate = false;
    static constexpr bool bCanBeDisabled = false;
    
    // std::string Name = "Transform";
    
    CTransformComponent() {}
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
    
    Vector3 Position = {0,0,0};
    Vector3 Rotation = {0,0,0};
    Vector3 Scale = {1,1,1};
};
