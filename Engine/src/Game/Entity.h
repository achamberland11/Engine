#pragma once
#include "Component.h"
#include "Object.h"

class GEntity : public GObject
{
public:
    GENERATE_REFLECTION()
    
    friend class CEntityPropertyRegistrar;

    GEntity();
    virtual ~GEntity();
    
    virtual void Start();
    virtual void Update(float deltaSeconds);
    
    std::string GetName() const { return Name; }
    void SetName(const std::string& name) { Name = name; }
    bool* Active() { return &bActive; }
    bool IsActive() const { return bActive; }
    void SetActive(bool active) { bActive = active; }

    void SetParent(GEntity* parent);
    void AddChild(GEntity* child);
    void RemoveChild(GEntity* child);
    
    GEntity* GetRoot();
    GEntity* GetParent() const { return Parent; }
    const std::vector<GEntity*>& GetChildren() const { return Children; }
    const std::vector<GComponent*>& GetComponents() const { return Components; }

    void AddComponent(GComponent* component);
    void RemoveComponent(GComponent* component);
    
protected:
    std::string Name = "Entity";
    bool bActive = true;
    
    std::vector<GComponent*> Components;
    GEntity* Parent = nullptr;
    std::vector<GEntity*> Children;
    
};
