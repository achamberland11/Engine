#include "Entity.h"
#include <algorithm>

#include "../Core/GameEngine.h"
#include "Components/ComponentsLinker.h"
#include "Entities/EntityRegistry.h"
#include "../Factories/EntityFactory.hpp"

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
        REGISTER_PROPERTY(GEntity, "Name", Name, EPropertyType::String)
        REGISTER_PROPERTY(GEntity, "Active", bActive, EPropertyType::Bool)
    }
};

static CEntityPropertyRegistrar sEntityPropertyRegistrar;

class CEntityRegistrar
{
public:
    CEntityRegistrar()
    {
        REGISTER_ENTITY(GEntity)
    }
};

static CEntityRegistrar sEntityRegistrar;

GEntity::GEntity()
{
    GTransformComponent::StaticClass().Factory(this, Name);
}

GEntity::~GEntity()
{
    for (auto child : Children)
    {
        if (child) child->Parent = nullptr;
    }
    Children.clear();

    if (Parent) Parent->RemoveChild(this);

    for (auto component : Components) CGameEngine::Instance().FreeObject(component);
    Components.clear();
}

void GEntity::Start()
{
    for (auto component : Components) component->Start();
    SDL_Log("Start %s", Name.c_str());
}

void GEntity::Update(float deltaSeconds)
{
    for (auto component : Components) component->Update(deltaSeconds);
}

void GEntity::SetParent(GEntity* parent)
{
    if (Parent == parent) return;
    if (Parent) Parent->RemoveChild(this);
    Parent = parent;
    if (Parent) Parent->AddChild(this);
}

void GEntity::AddChild(GEntity* child)
{
    if (!child) return;
    if (child->Parent == this) return;
    Children.push_back(child);
    child->Parent = this;
}

void GEntity::RemoveChild(GEntity* child)
{
    if (!child) return;
    auto it = std::find(Children.begin(), Children.end(), child);
    if (it != Children.end())
    {
        Children.erase(it);
        child->Parent = nullptr;
    }
}

GEntity* GEntity::GetRoot()
{
    GEntity* current = this;
    while (current->Parent)
    {
        current = current->Parent;
    }
    return current;
}

void GEntity::AddComponent(GComponent* component)
{
    Components.push_back(component);
}

void GEntity::RemoveComponent(GComponent* component)
{
    auto it = std::find(Components.begin(), Components.end(), component);
    if (it != Components.end()) Components.erase(it);
    CGameEngine::Instance().FreeObject(component);
}