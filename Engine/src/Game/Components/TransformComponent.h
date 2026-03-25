#pragma once
#include "../Component.h"
#include "../../Structs/Vectors.h"
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
    
    FVector3 Position = {0,0,0};
    FVector3 Rotation = {0,0,0};
    FVector3 Scale = {1,1,1};
};
