#include "ColliderComponent.h"

#include "../ComponentRegistry.h"
#include "../../../Factories/ComponentFactory.hpp"


CClass CColliderComponent::sClass = CClass
{
    "ColliderComponent",
    &CComponent::StaticClass()
};

// Property Registration
std::vector<CProperty> CColliderComponent::sProperties;

class CColliderComponentPropertyRegistrar
{
public:
    CColliderComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY(CColliderComponent, "Component Name", Name, EPropertyType::String);
        REGISTER_PROPERTY(CColliderComponent, "Enabled", bEnabled, EPropertyType::Bool);
        
        CColliderComponent::StaticClass().Properties = CColliderComponent::ClassProperties();
    }
};

static CColliderComponentPropertyRegistrar sColliderComponentPropertyRegistrar;

// Component Class Registration
class CColliderComponentRegistrar
{
public:
    CColliderComponentRegistrar()
    {
        CColliderComponent::StaticClass().Factory = [](CEntity* entity)
        {
            static ComponentFactory compFactory;
            compFactory.NewComponent<CColliderComponent>(entity);
        };
        
        CComponentRegistry::Instance().RegisterComponent(CColliderComponent::StaticClass());
    }
};

static CColliderComponentRegistrar sColliderComponentRegistrar;