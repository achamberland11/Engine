#include "Component.h"

CClass CComponent::sClass = CClass{
    "Component",
   &GObject::StaticClass() 
};

std::vector<CProperty> CComponent::sProperties;

class CEntityPropertyRegistrar
{
public:
    CEntityPropertyRegistrar()
    {
        REGISTER_PROPERTY(CComponent, "Component Name", Name, EPropertyType::String);
        REGISTER_PROPERTY(CComponent, "Enabled", bEnabled, EPropertyType::Bool);

        CComponent::StaticClass().Properties = CComponent::ClassProperties();
    }
};

static CEntityPropertyRegistrar sEntityPropertyRegistrar;
