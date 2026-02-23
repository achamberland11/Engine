#pragma once
#include <string>

class CClass
{
public:
    std::string Name;
    const CClass* Parent;

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
};

