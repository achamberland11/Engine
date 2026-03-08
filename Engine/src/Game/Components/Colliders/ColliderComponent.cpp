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
// std::vector<CProperty> CColliderComponent::sProperties;

class CColliderComponentPropertyRegistrar
{
public:
    CColliderComponentPropertyRegistrar()
    {
        GColliderComponent::StaticClass().bCanDuplicate = GColliderComponent::bCanDuplicate;
    }
};

static CColliderComponentPropertyRegistrar sColliderComponentPropertyRegistrar;

// Component Class Registration
class CColliderComponentRegistrar
{
public:
    CColliderComponentRegistrar()
    {
        REGISTER_COMPONENT(GColliderComponent);
    }
};

static CColliderComponentRegistrar sColliderComponentRegistrar;