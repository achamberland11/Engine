#include "Component.h"

CClass GComponent::sClass = CClass{
    "CComponent",
    "Component",
    &GObject::StaticClass() 
};

// std::vector<CProperty> CComponent::sProperties;

class CComponentPropertyRegistrar
{
public:
    CComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY(GComponent, "Name", Name, EPropertyType::String);
        REGISTER_PROPERTY(GComponent, "Enabled", bEnabled, EPropertyType::Bool);

        GComponent::StaticClass().bCanDuplicate = GComponent::bCanDuplicate;
    }
};

static CComponentPropertyRegistrar sComponentPropertyRegistrar;
