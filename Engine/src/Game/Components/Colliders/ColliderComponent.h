#pragma once

#include "../../Component.h"


class GColliderComponent : public GComponent
{
public:
    GENERATE_REFLECTION()
    GENERATE_COMPONENT(true, true, true, true)
    
    GColliderComponent()
    {
        Name = "Collider";
    }
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
   
    EColliderType3D ColliderType3D = EColliderType3D::Box;
};
