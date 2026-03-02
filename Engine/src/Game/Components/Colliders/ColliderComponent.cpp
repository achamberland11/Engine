#include "ColliderComponent.h"

#include "../ComponentRegistry.h"
#include "../../../Factories/ComponentFactory.hpp"


CClass CColliderComponent::sClass = CClass
{
    "CColliderComponent",
    "Collider",
    &CComponent::StaticClass()
};

// Property Registration
// std::vector<CProperty> CColliderComponent::sProperties;

class CColliderComponentPropertyRegistrar
{
public:
    CColliderComponentPropertyRegistrar()
    {
        CColliderComponent::StaticClass().bCanDuplicate = CColliderComponent::bCanDuplicate;
    }
};

static CColliderComponentPropertyRegistrar sColliderComponentPropertyRegistrar;

// Component Class Registration
class CColliderComponentRegistrar
{
public:
    CColliderComponentRegistrar()
    {
        REGISTER_COMPONENT(CColliderComponent);
    }
};

static CColliderComponentRegistrar sColliderComponentRegistrar;