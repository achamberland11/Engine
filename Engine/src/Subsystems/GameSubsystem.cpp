#include "GameSubsystem.h"
#include <numeric>

#include "../../SDL/include/SDL3/SDL_keycode.h"
#include "../../SDL/include/SDL3/SDL_stdinc.h"
#include "../Core/GameEngine.h"

void CGameSubsystem::Start()
{
    FrameDuration.reserve(100);
    
    EditorMode = CGameEngine::Instance().GetEditor().GetEditorMode();
}

void CGameSubsystem::Shutdown()
{
    EditorMode = nullptr;
}

void CGameSubsystem::Update(float deltaSeconds)
{
    // TODO: Move this in another subsystem or in the CCounter
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

    //if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_ESCAPE))
    //    CGameEngine::Instance().Quit();

    //if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_SPACE))
    //   BackgroundColor = { (float)(rand() % 256) / 255.0f, (float)(rand() % 256) / 255.0f, (float)(rand() % 256) / 255.0f };

    if (*EditorMode == Editor )
        return;
    
    if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_ESCAPE))
        CGameEngine::Instance().GetEditor().ExitPlayMode();

    if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_F5) && *EditorMode == Play)
        CGameEngine::Instance().GetEditor().EnterPauseMode();
    else if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_F5) && *EditorMode == Pause)
        CGameEngine::Instance().GetEditor().EnterPlayMode();

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
