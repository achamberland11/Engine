#include "Class.h"

CClass::CClass(std::string name, std::string displayName, const CClass* parent)
    : ClassName(name), DisplayName(displayName), Parent(parent)
{
    if (Parent != nullptr)
    {
        const CClass* currentParent = Parent;
        while (currentParent != nullptr)
        {
            for (const CProperty& property : currentParent->Properties)
            {
                AddProperty(property);
            }
            currentParent = currentParent->Parent;
        }
    }
}
