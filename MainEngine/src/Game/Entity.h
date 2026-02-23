#pragma once
#include "Component.h"
#include "Object.h"

class CEntity : public GObject
{
public:
    GENERATE_REFLECTION()

    CEntity() = default;
    virtual ~CEntity() = default;

    std::string Name = "Entity";
    bool bActive = true;
    std::vector<CComponent*> Components;

    void AddComponent(CComponent* component);
    void RemoveComponent(CComponent* component);
    // CComponent* GetComponent(const std::string& name);
};
