#pragma once

#include "../../Component.h"


class CColliderComponent : public CComponent
{
public:
    GENERATE_REFLECTION()
    
    CColliderComponent()
    {
        Name = "Collider";
    }
    
    void Start() override {}
    void Update(float deltaSeconds) override {}
    
    static constexpr bool bCanDuplicate = true;
    static constexpr bool bCanBeDisabled = true;
    static constexpr bool bCanBeDeleted = true;
};
