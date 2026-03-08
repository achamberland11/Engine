#pragma once

#include "../../Component.h"


class GColliderComponent : public GComponent
{
public:
    GENERATE_REFLECTION()
    GENERATE_COMPONENT(true, true, true)
    
    GColliderComponent()
    {
        Name = "Collider";
    }
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
};
