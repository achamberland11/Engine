#include "TransformComponent.h"

#include <vector>

// Reflection class info (display name + parent class)
CClass CTransformComponent::sClass = CClass
{
    "Transform",
    &CComponent::StaticClass()
};

std::vector<CProperty> CTransformComponent::sProperties;

class CTransformComponentPropertyRegistrar
{
public:
    CTransformComponentPropertyRegistrar()
    {
        REGISTER_PROPERTY(CTransformComponent, "Position", Position, EPropertyType::Vector3);
        REGISTER_PROPERTY(CTransformComponent, "Rotation", Rotation, EPropertyType::Vector3);
        REGISTER_PROPERTY(CTransformComponent, "Scale",    Scale,    EPropertyType::Vector3);

        CTransformComponent::StaticClass().Properties = CTransformComponent::ClassProperties();
    }
};

static CTransformComponentPropertyRegistrar sTransformComponentPropertyRegistrar;