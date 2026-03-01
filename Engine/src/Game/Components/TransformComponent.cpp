#include "TransformComponent.h"

#include <vector>

#include "ComponentRegistry.h"
#include "../../Factories/ComponentFactory.hpp"

CClass CTransformComponent::sClass = CClass
{
    "TransformComponent",
    &CComponent::StaticClass()
};

// Property Registration
std::vector<CProperty> CTransformComponent::sProperties;

class CTransformComponentPropertyRegistrar
{
public:
    CTransformComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY(CTransformComponent, "Component Name", Name, EPropertyType::String);
        REGISTER_PROPERTY(CTransformComponent, "Enabled", bEnabled, EPropertyType::Bool);
        
        REGISTER_PROPERTY(CTransformComponent, "Position", Position, EPropertyType::Vector3);
        REGISTER_PROPERTY(CTransformComponent, "Rotation", Rotation, EPropertyType::Vector3);
        REGISTER_PROPERTY(CTransformComponent, "Scale", Scale, EPropertyType::Vector3);

        CTransformComponent::StaticClass().Properties = CTransformComponent::ClassProperties();
    }
};

static CTransformComponentPropertyRegistrar sTransformComponentPropertyRegistrar;


// Component Class Registration
class CTransformComponentRegistrar
{
public:
    CTransformComponentRegistrar()
    {
        CTransformComponent::StaticClass().Factory = [](CEntity* entity)
        {
            static ComponentFactory compFactory;
            compFactory.NewComponent<CTransformComponent>(entity);
        };

        CComponentRegistry::Instance().RegisterComponent(CTransformComponent::StaticClass());
        // REGISTER_COMPONENT(CTransformComponent);
    }
};

static CTransformComponentRegistrar sTransformComponentRegistrar;
