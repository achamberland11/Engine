#pragma once
#include "Component.h"
#include "Object.h"

class CEntity : public GObject
{
public:
    GENERATE_REFLECTION()

    CEntity();
    virtual ~CEntity();

    std::string Name = "Entity";
    bool bActive = true;
    std::vector<CComponent*> Components;

    void AddComponent(CComponent* component);
    void RemoveComponent(CComponent* component);
    std::vector<CComponent*> GetComponents();
};
