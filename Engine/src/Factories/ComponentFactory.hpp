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
            if (component->IsA(T::StaticClass()))
            {
                bComponentExists = true;
                break;
            }
        }
        
        if (bComponentExists) return;
    }
    GComponent* newComponent = CGameEngine::Instance().NewObject<T>();
    // newComponent->Start();
    
    if (!newComponent->IsA(GComponent::StaticClass()))
    {
        CGameEngine::Instance().FreeObject(newComponent);
        return;
    }
    parent->AddComponent(newComponent);
}

