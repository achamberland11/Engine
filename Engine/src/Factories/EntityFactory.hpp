#pragma once
#include "../Entity.h"
#include "../Game/Entity.h"

class CEntityFactory
{
public:
    template <typename T>
    void NewEntity(GEntity* parentEntity = nullptr);
};

template <typename T>
void CEntityFactory::NewEntity(GEntity* parentEntity)
{
    GEntity* newEntity = CGameEngine::Instance().NewObject<T>();

    assert(newEntity->IsA(GEntity::StaticClass()), "Entity is not a GEntity");
    if (!newEntity->IsA(GEntity::StaticClass())) return;

    // newEntity->Start();
    if (parentEntity != nullptr)
    {
        parentEntity->AddChild(newEntity);
        newEntity->SetParent(parentEntity);
    }
}
