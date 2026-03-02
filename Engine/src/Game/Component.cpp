#include "Component.h"

CClass CComponent::sClass = CClass{
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
        REGISTER_PROPERTY(CComponent, "Name", Name, EPropertyType::String);
        REGISTER_PROPERTY(CComponent, "Enabled", bEnabled, EPropertyType::Bool);

        CComponent::StaticClass().bCanDuplicate = CComponent::bCanDuplicate;
    }
};

static CComponentPropertyRegistrar sComponentPropertyRegistrar;
