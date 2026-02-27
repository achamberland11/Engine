#pragma once

#include "../Core/GameEngine.h"
#include "../Game/Entity.h"
#include "../Game/Component.h"

class ComponentFactory
{
public:
    template <typename T> void NewComponent(CEntity* parent);
    
};

template <typename T>
void ComponentFactory::NewComponent(CEntity* parent)
{
    if (parent == nullptr) return;
    
    if (!T::bCanDuplicate)
    {
        bool bComponentExists = false;
        for (CComponent* component : parent->GetComponents())
        {
            if (component->IsA(CComponent::StaticClass()))
            {
                bComponentExists = true;
                break;
            }
        }
        
        if (bComponentExists) return;
    }
    CComponent* newComponent = CGameEngine::Instance().NewObject<T>();
    newComponent->Start();
    parent->AddComponent(newComponent);
}

