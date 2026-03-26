#include "Component.h"

CClass GComponent::sClass = CClass{
    "CComponent",
    "Component",
    &GObject::StaticClass() 
};

void GComponent::SetEnabled(bool enabled)
{
    if (GetClass()->bCanDisable)
    {
        bEnabled = enabled;
    }
    else
    {
        // TODO : Add Console.Log functionalities
        // GLog::Warning("Component %s cannot be disabled", GetName());
    }
}

// std::vector<CProperty> CComponent::sProperties;

class CComponentPropertyRegistrar
{
public:
    CComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY_EX(GComponent, "Name", Name, EPropertyType::String, false);
        REGISTER_PROPERTY(GComponent, "Enabled", bEnabled, EPropertyType::Bool);

        GComponent::StaticClass().bCanDuplicate = GComponent::bCanDuplicate;
        GComponent::StaticClass().bCanDelete = GComponent::bCanBeDeleted;
        GComponent::StaticClass().bCanDisable = GComponent::bCanBeDisabled;
    }
};

static CComponentPropertyRegistrar sComponentPropertyRegistrar;
