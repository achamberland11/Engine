#pragma once

#include "../Core/GameEngine.h"
#include "../Game/Entity.h"
#include "../Game/Component.h"

class CComponentFactory
{
public:
    template <typename T> void NewComponent(GEntity* parent);
    
};

template <typename T>
void CComponentFactory::NewComponent(GEntity* parent)
{
    if (parent == nullptr) return;
    
    if (!T::bCanDuplicate)
    {
        bool bComponentExists = false;
        for (GComponent* component : parent->GetComponents())
        {
            if (component->IsA(GComponent::StaticClass()))
            {
                bComponentExists = true;
                break;
            }
        }
        
        if (bComponentExists) return;
    }
    GComponent* newComponent = CGameEngine::Instance().NewObject<T>();
    // newComponent->Start();
    
    assert(newComponent->IsA(GComponent::StaticClass()), "Component is not a component");
    if (!newComponent->IsA(GComponent::StaticClass())) return;
    parent->AddComponent(newComponent);
}

