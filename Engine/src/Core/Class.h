#pragma once
#include <functional>
#include <string>
#include <vector>

// #include "../Game/Entity.h"
#include "../Structs/Property.h"

class CEntity;

class CClass
{
public:
    std::string Name;
    const CClass* Parent;
    std::vector<CProperty> Properties;
    std::function<void(CEntity*)> Factory;

    const std::string& GetName() const { return Name; }
    const CClass* GetParent() const { return Parent; }

    bool IsChildOf(const CClass* other) const
    {
        const CClass* current = this;
        while (current != nullptr)
        {
            if (current == other) return true;
            current = current->GetParent();
        }
        return false;
    }

    void AddProperty(const CProperty& property) { Properties.push_back(property); }

    const CProperty* FindProperty(const std::string& name) const
    {
        for (const CProperty& property : Properties)
            if (property.Name == name) return &property;
        
        return nullptr;
    }
};

