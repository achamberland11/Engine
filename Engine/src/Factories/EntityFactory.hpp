#pragma once
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

    if (!newEntity->IsA(GEntity::StaticClass()))
    {
        CGameEngine::Instance().FreeObject(newEntity);
        return;
    }

    // newEntity->Start();
    if (parentEntity != nullptr)
    {
        parentEntity->AddChild(newEntity);
        newEntity->SetParent(parentEntity);
    }
}
