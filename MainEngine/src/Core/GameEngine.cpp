#include "GameEngine.h"

#include "SDL3/SDL_timer.h"

void CGameEngine::Init()
{
    rendererSubsystem.Start();
    inputSubsystem.Start();
    gameSubsystem.Start();
}

void CGameEngine::Loop()
{
    static float lastTime = SDL_GetTicks();
    float currentTime = SDL_GetTicks();
    float deltaSeconds = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    inputSubsystem.Update(deltaSeconds);
    gameSubsystem.Update(deltaSeconds);
    counter.Update(deltaSeconds);

    float avg = gameSubsystem.GetAverageFrameTime();
    int fps = counter.GetFPS();
    rendererSubsystem.SetFrameTimeText("Average Frame Time: " + std::to_string(avg) + "s");
    rendererSubsystem.SetFPSText("FPS: " + std::to_string(fps));

    Color bgColor = gameSubsystem.GetBackgroundColor();
    rendererSubsystem.SetClearColor(bgColor);
    
    rendererSubsystem.Update(deltaSeconds);
}

void CGameEngine::Shutdown()
{
    inputSubsystem.Shutdown();
    gameSubsystem.Shutdown();
    rendererSubsystem.Shutdown();
}
