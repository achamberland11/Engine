#include "Scene.h"

#include "GameEngine.h"

CScene::CScene()
{
}

CScene::~CScene()
{
    Clear();
}

void CScene::AddEntity(GEntity* entity)
{
    Entities.push_back(entity);
}

void CScene::RemoveEntity(GEntity* entity)
{
    auto it = std::find(Entities.begin(), Entities.end(), entity);
    if (it != Entities.end()) Entities.erase(it);
}

void CScene::Clear()
{
    for (auto entity : Entities) CGameEngine::Instance().DestroyEntity(entity);
    Entities.clear();
}
