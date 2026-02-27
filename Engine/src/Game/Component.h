#pragma once
#include "Object.h"

class CComponent : public GObject
{
public:
    GENERATE_REFLECTION()

    CComponent() {}
    virtual ~CComponent() = default;
    
    virtual void Start() = 0;
    virtual void Update(float deltaSeconds) = 0;
    
    std::string Name = "Component";
    bool bEnabled = true;
    
    static constexpr bool bCanDuplicate = true;
    static constexpr bool bCanBeDisabled = true;
    
};
