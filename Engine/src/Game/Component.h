#pragma once
#include "Object.h"

class GComponent : public GObject
{
public:
    GENERATE_REFLECTION()
    GENERATE_COMPONENT(true, true, true, false)
    
    friend class CComponentPropertyRegistrar;

    GComponent() = default;
    virtual ~GComponent() = default;
    
    virtual void Start() = 0;
    virtual void Update(float deltaSeconds) = 0;
    
    const char* GetName() const { return Name.c_str(); }
    void SetName(const std::string& name) { Name = name; }
    bool IsEnabled() const { return bEnabled; }
    void SetEnabled(bool enabled);
    
protected: 
    std::string Name = "Component";
    bool bEnabled = true;
};
