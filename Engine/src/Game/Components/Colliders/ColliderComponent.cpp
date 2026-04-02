#include "ColliderComponent.h"

#include "../ComponentRegistry.h"
#include "../../../Factories/ComponentFactory.hpp"


CClass GColliderComponent::sClass = CClass
{
    "CColliderComponent",
    "Collider",
    &GComponent::StaticClass()
};

// Property Registration
class CColliderComponentPropertyRegistrar
{
public:
    CColliderComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY(GColliderComponent, "Collider Type", ColliderType3D, EPropertyType::ColliderType3D)
        
        GColliderComponent::StaticClass().bCanDuplicate = GColliderComponent::bCanDuplicate;
        GColliderComponent::StaticClass().bCanBeDeleted = GColliderComponent::bCanBeDeleted;
        GColliderComponent::StaticClass().bCanBeDisabled = GColliderComponent::bCanBeDisabled;
        GColliderComponent::StaticClass().bUpdateInEditor = GColliderComponent::bUpdateInEditor;
    }
};

static CColliderComponentPropertyRegistrar sColliderComponentPropertyRegistrar;

// Component Class Registration
class CColliderComponentRegistrar
{
public:
    CColliderComponentRegistrar()
    {
        REGISTER_COMPONENT(GColliderComponent)
    }
};

static CColliderComponentRegistrar sColliderComponentRegistrar;