#include "GameEngine.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "SDL3/SDL_timer.h"

void CGameEngine::Init()
{
    RendererSubsystem.Start();
    InputSubsystem.Start();
    GameSubsystem.Start();
}

void CGameEngine::Loop()
{
    RendererSubsystem.OnBeginFrame();
    
    static float lastTime = SDL_GetTicks();
    float currentTime = SDL_GetTicks();
    float deltaSeconds = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    InputSubsystem.Update(deltaSeconds);
    GameSubsystem.Update(deltaSeconds);
    Counter.Update(deltaSeconds);

    float avg = GameSubsystem.GetAverageFrameTime();
    int fps = Counter.GetFPS();
    RendererSubsystem.SetFrameTimeText("Average Frame Time: " + std::to_string(avg) + "s");
    RendererSubsystem.SetFPSText("FPS: " + std::to_string(fps));

    FColor bgColor = GameSubsystem.GetBackgroundColor();
    RendererSubsystem.SetClearColor(bgColor);
    
    RendererSubsystem.Update(deltaSeconds);
    RendererSubsystem.OnEndFrame();
}

void CGameEngine::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    GameSubsystem.Shutdown();
    InputSubsystem.Shutdown();
    RendererSubsystem.Shutdown();
}
