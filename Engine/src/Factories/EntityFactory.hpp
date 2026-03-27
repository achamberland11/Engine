#pragma once
#include "../Game/Entity.h"

class CEntityFactory
{
public:
    template <typename T>
    void NewEntity(GEntity* parentEntity = nullptr, std::string name = "");
};

template <typename T>
void CEntityFactory::NewEntity(GEntity* parentEntity, std::string name)
{
    if (name.empty())
    {
        name = T::StaticClass().DisplayName;
    }
    GEntity* newEntity = CGameEngine::Instance().CreateEntity(name);

    if (!newEntity->IsA(GEntity::StaticClass()))
    {
        CGameEngine::Instance().DestroyEntity(newEntity);
        return;
    }

    if (parentEntity != nullptr)
    {
        parentEntity->AddChild(newEntity);
        newEntity->SetParent(parentEntity);
    }
}
