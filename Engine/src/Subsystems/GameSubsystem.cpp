#include "GameSubsystem.h"
#include <numeric>

#include "../../SDL/include/SDL3/SDL_keycode.h"
#include "../../SDL/include/SDL3/SDL_stdinc.h"
#include "../Core/GameEngine.h"

void CGameSubsystem::Start()
{
    FrameDuration.reserve(100);
}

void CGameSubsystem::Shutdown() {}

void CGameSubsystem::Update(float deltaSeconds)
{
    if (FrameDuration.size() >= 100)
    {
        FrameDuration.erase(FrameDuration.begin());
    }
    FrameDuration.push_back(deltaSeconds);

    TimeAccumulator += deltaSeconds;

    if (TimeAccumulator >= 0.5f)
    {
        if (!FrameDuration.empty())
        {
            float sum = std::accumulate(FrameDuration.begin(), FrameDuration.end(), 0.0f);
            CurrentAverage = sum / FrameDuration.size();
        }
        TimeAccumulator = 0.0f;
    }

    if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_ESCAPE))
        CGameEngine::Instance().Quit();

    if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_SPACE))
        BackgroundColor = { (float)(rand() % 256) / 255.0f, (float)(rand() % 256) / 255.0f, (float)(rand() % 256) / 255.0f };

}

GEntity* CGameSubsystem::CreateEntity(const std::string& name)
{
    GEntity* newEntity = CGameEngine::Instance().NewObject<GEntity>();
    newEntity->SetName(name);
    Entities.push_back(newEntity);
    return newEntity;
}

void CGameSubsystem::DestroyEntity(GEntity* entity)
{
    auto it = std::find(Entities.begin(), Entities.end(), entity);
    if (it != Entities.end()) Entities.erase(it);
    CGameEngine::Instance().FreeObject(entity);
}
