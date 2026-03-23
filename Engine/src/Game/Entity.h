#pragma once
#include "Component.h"
#include "Object.h"

class GEntity : public GObject
{
public:
    GENERATE_REFLECTION()

    GEntity();
    virtual ~GEntity();

    std::string Name = "Entity";
    bool bActive = true;
    std::vector<GComponent*> Components;

    GEntity* Parent = nullptr;
    std::vector<GEntity*> Children;

    void SetParent(GEntity* parent);
    void AddChild(GEntity* child);
    void RemoveChild(GEntity* child);
    GEntity* GetRoot();

    void AddComponent(GComponent* component);
    void RemoveComponent(GComponent* component);
    std::vector<GComponent*> GetComponents();
};
