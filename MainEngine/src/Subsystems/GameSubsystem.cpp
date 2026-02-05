#include "GameSubsystem.h"
#include <numeric>

#include "../../SDL/include/SDL3/SDL_keycode.h"
#include "../../SDL/include/SDL3/SDL_stdinc.h"
#include "../Core/GameEngine.h"

void CGameSubsystem::Start()
{
    frameDuration.reserve(100);
}

void CGameSubsystem::Shutdown() {}

void CGameSubsystem::Update(float deltaSeconds)
{
    if (frameDuration.size() >= 100)
    {
        frameDuration.erase(frameDuration.begin());
    }
    frameDuration.push_back(deltaSeconds);

    timeAccumulator += deltaSeconds;

    if (timeAccumulator >= 0.5f)
    {
        if (!frameDuration.empty())
        {
            float sum = std::accumulate(frameDuration.begin(), frameDuration.end(), 0.0f);
            currentAverage = sum / frameDuration.size();
        }
        timeAccumulator = 0.0f;
    }

    if (CGameEngine::Instance().GetInput().GetButtonState(SDLK_ESCAPE) == EButtonState::JUST_PRESSED)
        CGameEngine::Instance().Shutdown();

    if (CGameEngine::Instance().GetInput().GetButtonState(SDLK_SPACE) == EButtonState::JUST_PRESSED)
        backgroundColor = { (Uint8)(rand() % 255), (Uint8)(rand() % 255), (Uint8)(rand() % 255) };
}
