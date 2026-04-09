#include "ColliderComponent2D.h"

#include "../ComponentRegistry.h"
#include "../../../Factories/ComponentFactory.hpp"


CClass GColliderComponent2D::sClass = CClass
{
    "CColliderComponent2D",
    "Collider2D",
    &GComponent::StaticClass()
};

// Property Registration
class CColliderComponent2DPropertyRegistrar
{
public:
    CColliderComponent2DPropertyRegistrar()
    {
        REGISTER_PROPERTY(GColliderComponent2D, "Collider Type", ColliderType2D, EPropertyType::ColliderType2D)
        
        GColliderComponent2D::StaticClass().bCanDuplicate = GColliderComponent2D::bCanDuplicate;
        GColliderComponent2D::StaticClass().bCanBeDeleted = GColliderComponent2D::bCanBeDeleted;
        GColliderComponent2D::StaticClass().bCanBeDisabled = GColliderComponent2D::bCanBeDisabled;
        GColliderComponent2D::StaticClass().bUpdateInEditor = GColliderComponent2D::bUpdateInEditor;
    }
};

static CColliderComponent2DPropertyRegistrar sColliderComponent2DPropertyRegistrar;

// Component Class Registration
class CColliderComponent2DRegistrar
{
public:
    CColliderComponent2DRegistrar()
    {
        REGISTER_COMPONENT(GColliderComponent2D)
    }
};

static CColliderComponent2DRegistrar sColliderComponent2DRegistrar;