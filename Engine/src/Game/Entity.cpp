#include "Entity.h"
#include <algorithm>

#include "../Core/GameEngine.h"
#include "Components/TransformComponent.h"

CClass GEntity::sClass = CClass{
    "CEntity",
    "Entity",
    &GObject::StaticClass() 
};

// std::vector<CProperty> CEntity::sProperties;

class CEntityPropertyRegistrar
{
public:
    CEntityPropertyRegistrar()
    {
        REGISTER_PROPERTY(GEntity, "Name", Name, EPropertyType::String);
        REGISTER_PROPERTY(GEntity, "Active", bActive, EPropertyType::Bool);

        // CEntity::StaticClass().Properties = CEntity::ClassProperties();
    }
};

static CEntityPropertyRegistrar sEntityPropertyRegistrar;

GEntity::GEntity()
{
    GTransformComponent::StaticClass().Factory(this);
}

GEntity::~GEntity()
{
    for (auto component : Components) CGameEngine::Instance().FreeObject(component);
    Components.clear();
}

void GEntity::AddComponent(GComponent* component)
{
    Components.push_back(component);
}

void GEntity::RemoveComponent(GComponent* component)
{
    auto it = std::find(Components.begin(), Components.end(), component);
    if (it != Components.end()) Components.erase(it);
}

std::vector<GComponent*> GEntity::GetComponents()
{
    return Components;
}
