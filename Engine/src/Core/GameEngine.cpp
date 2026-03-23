#include "GameEngine.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "SDL3/SDL_timer.h"

void CGameEngine::Init()
{
    RendererSubsystem.Start();
    InputSubsystem.Start();
    GameSubsystem.Start();
    EditorSubsystem.Start();
    
    int allocatorSize = GetAllocator().GetSize();
    int allocatorPageSize = GetAllocator().GetPageSize();
    int allocatorPages = GetAllocator().GetPagesCount();
    EditorSubsystem.GetWindowManager().GetWindow<CDebugWindow>()->SetMemoryStats(allocatorSize, allocatorPageSize, allocatorPages);
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
    EditorSubsystem.Update(deltaSeconds);
    Counter.Update(deltaSeconds);

    FColor bgColor = GameSubsystem.GetBackgroundColor();
    RendererSubsystem.SetClearColor(bgColor);

    float avg = GameSubsystem.GetAverageFrameTime();
    int fps = Counter.GetFPS();
    int usedPages = GetAllocator().GetUsedPages();
    int reservedPages = GetAllocator().GetReservedPages();
    int allocatorUsed = GetAllocator().GetUsedSize();
    int allocatorReserved = GetAllocator().GetReservedSize();

    EditorSubsystem.GetWindowManager().GetWindow<CDebugWindow>()->SetFPS(fps);
    EditorSubsystem.GetWindowManager().GetWindow<CDebugWindow>()->SetFrameTime(avg);
    EditorSubsystem.GetWindowManager().GetWindow<CDebugWindow>()->SetMemoryUsage(allocatorUsed, allocatorReserved, usedPages, reservedPages);

    RendererSubsystem.Update(deltaSeconds);
    RendererSubsystem.OnEndFrame();
}

void CGameEngine::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    EditorSubsystem.Shutdown();
    GameSubsystem.Shutdown();
    InputSubsystem.Shutdown();
    RendererSubsystem.Shutdown();
}
