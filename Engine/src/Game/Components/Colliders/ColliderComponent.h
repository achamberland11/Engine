#pragma once

#include "../../Component.h"


class CColliderComponent : public CComponent
{
public:
    GENERATE_REFLECTION()
    GENERATE_COMPONENT(true, true, true)
    
    CColliderComponent()
    {
        Name = "Collider";
    }
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
};
