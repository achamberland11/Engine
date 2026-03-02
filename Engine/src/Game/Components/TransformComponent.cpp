#include "TransformComponent.h"

#include <vector>

#include "ComponentRegistry.h"
#include "../../Factories/ComponentFactory.hpp"

CClass CTransformComponent::sClass = CClass
{
    "CTransformComponent",
    "Transform",
    &CComponent::StaticClass()
};

// Property Registration
// std::vector<CProperty> CTransformComponent::sProperties;

class CTransformComponentPropertyRegistrar
{
public:
    CTransformComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY(CTransformComponent, "Position", Position, EPropertyType::Vector3);
        REGISTER_PROPERTY(CTransformComponent, "Rotation", Rotation, EPropertyType::Vector3);
        REGISTER_PROPERTY(CTransformComponent, "Scale", Scale, EPropertyType::Vector3);

        CTransformComponent::StaticClass().bCanDuplicate = CTransformComponent::bCanDuplicate;
    }
};

static CTransformComponentPropertyRegistrar sTransformComponentPropertyRegistrar;


// Component Class Registration
class CTransformComponentRegistrar
{
public:
    CTransformComponentRegistrar()
    {
        REGISTER_COMPONENT(CTransformComponent);
    }
};

static CTransformComponentRegistrar sTransformComponentRegistrar;
