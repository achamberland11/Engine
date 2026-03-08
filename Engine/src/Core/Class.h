#pragma once
#include <functional>
#include <string>
#include <vector>

// #include "../Game/Entity.h"
#include "../Structs/Property.h"
#include "SDL3/SDL_log.h"

class GEntity;

class CClass
{
public:
    CClass(std::string name, std::string displayName, const CClass* parent);
    
    std::string ClassName;
    std::string DisplayName = ClassName;
    const CClass* Parent;
    std::vector<FProperty> Properties;
    std::function<void(GEntity*)> Factory;
    bool bCanDuplicate = true;

    const std::string& GetName() const { return ClassName; }
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

    void AddProperty(const FProperty& property)
    {
        Properties.push_back(property);
        SDL_Log("Added property %s to class %s", property.Name.c_str(), ClassName.c_str());
    }

    const FProperty* FindProperty(const std::string& name) const
    {
        for (const FProperty& property : Properties)
            if (property.Name == name) return &property;

        return nullptr;
    }
};