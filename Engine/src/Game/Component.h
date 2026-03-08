#pragma once
#include "Object.h"

class GComponent : public GObject
{
public:
    GENERATE_REFLECTION()
    GENERATE_COMPONENT(true, true, true)

    GComponent() {}
    virtual ~GComponent() = default;
    
    virtual void Start() = 0;
    virtual void Update(float deltaSeconds) = 0;
    
    virtual bool CanDuplicate() const { return bCanDuplicate; }
    virtual bool CanBeDisabled() const { return bCanBeDisabled; }
    virtual bool CanBeDeleted() const { return bCanBeDeleted; }
    
    
    std::string Name = "Component";
    bool bEnabled = true;
};
