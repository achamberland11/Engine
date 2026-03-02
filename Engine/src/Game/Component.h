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
    
    virtual bool CanDuplicate() const { return bCanDuplicate; }
    virtual bool CanBeDisabled() const { return bCanBeDisabled; }
    virtual bool CanBeDeleted() const { return bCanBeDeleted; }
    
    static constexpr bool bCanDuplicate = true;
    static constexpr bool bCanBeDisabled = true;
    static constexpr bool bCanBeDeleted = true;
    
    
    std::string Name = "Component";
    bool bEnabled = true;
};
