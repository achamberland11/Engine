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

    void AddComponent(GComponent* component);
    void RemoveComponent(GComponent* component);
    std::vector<GComponent*> GetComponents();
};
