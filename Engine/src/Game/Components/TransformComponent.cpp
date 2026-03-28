#include "TransformComponent.h"

#include <vector>

#include "ComponentRegistry.h"
#include "../../Factories/ComponentFactory.hpp"

CClass GTransformComponent::sClass = CClass
{
    "CTransformComponent",
    "Transform",
    &GComponent::StaticClass()
};

// Property Registration
class CTransformComponentPropertyRegistrar
{
public:
    CTransformComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY(GTransformComponent, "Position", Position, EPropertyType::Vector3)
        REGISTER_PROPERTY(GTransformComponent, "Rotation", Rotation, EPropertyType::Vector3)
        REGISTER_PROPERTY(GTransformComponent, "Scale", Scale, EPropertyType::Vector3)

        GTransformComponent::StaticClass().bCanDuplicate = GTransformComponent::bCanDuplicate;
        GTransformComponent::StaticClass().bCanBeDeleted = GTransformComponent::bCanBeDeleted;
        GTransformComponent::StaticClass().bCanBeDisabled = GTransformComponent::bCanBeDisabled;
    }
};

static CTransformComponentPropertyRegistrar sTransformComponentPropertyRegistrar;

// Component Class Registration
class CTransformComponentRegistrar
{
public:
    CTransformComponentRegistrar()
    {
        REGISTER_COMPONENT(GTransformComponent)
    }
};

static CTransformComponentRegistrar sTransformComponentRegistrar;
