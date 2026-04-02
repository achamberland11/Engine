#include "GameEngine.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "SDL3/SDL_timer.h"

void CGameEngine::Init()
{
    CurrentScene = new CScene();
    // TODO: Load scene from file

    RendererSubsystem.Start();
    InputSubsystem.Start();
    EditorSubsystem.Start();
    GameSubsystem.Start();

    EditorMode = EditorSubsystem.GetEditorMode();

    int allocatorSize = GetAllocator().GetSize();
    int allocatorPageSize = GetAllocator().GetPageSize();
    int allocatorPages = GetAllocator().GetPagesCount();
    EditorSubsystem.GetWindowManager().GetWindow<EDebugWindow>()->SetMemoryStats(
        allocatorSize, allocatorPageSize, allocatorPages);
    
    
}

void CGameEngine::Loop()
{
    RendererSubsystem.OnBeginFrame();

    static float lastTime = static_cast<float>(SDL_GetTicks());
    float currentTime = static_cast<float>(SDL_GetTicks());
    float deltaSeconds = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    if (!GetCurrentScene()->IsLoadingScene())
    {
        InputSubsystem.Update(deltaSeconds);
        EditorSubsystem.Update(deltaSeconds);
        GameSubsystem.Update(deltaSeconds);
        Counter.Update(deltaSeconds);
    }

    switch (*EditorMode)
    {
    case Editor:
        if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_F5))
            EditorSubsystem.EnterPlayMode();
        if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_ESCAPE))
            Instance().Quit();
        break;
    case Play:
        if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_ESCAPE))
            Instance().GetEditor().ExitPlayMode();
        if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_F5))
            Instance().GetEditor().EnterPauseMode();
        break;
    case Pause:
        if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_ESCAPE))
            Instance().GetEditor().ExitPlayMode();
        if (CInputSubsystem::GetKeyPressed(SDL_SCANCODE_F5))
            Instance().GetEditor().EnterPlayMode();
        break;
    default:
        break;
    }


    FColor bgColor = GameSubsystem.GetBackgroundColor();
    RendererSubsystem.SetClearColor(bgColor);

    const float avg = GameSubsystem.GetAverageFrameTime();
    const float fps = Counter.GetFPS();
    const int usedPages = GetAllocator().GetUsedPages();
    const int reservedPages = GetAllocator().GetReservedPages();
    int allocatorUsed = GetAllocator().GetUsedSize();
    int allocatorReserved = GetAllocator().GetReservedSize();

    EditorSubsystem.GetWindowManager().GetWindow<EDebugWindow>()->SetFPS(fps);
    EditorSubsystem.GetWindowManager().GetWindow<EDebugWindow>()->SetFrameTime(avg);
    EditorSubsystem.GetWindowManager().GetWindow<EDebugWindow>()->SetMemoryUsage(
        allocatorUsed, allocatorReserved, usedPages, reservedPages);

    RendererSubsystem.Update(deltaSeconds);
    RendererSubsystem.OnEndFrame();
}

void CGameEngine::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    EditorMode = nullptr;

    GameSubsystem.Shutdown();
    EditorSubsystem.Shutdown();
    InputSubsystem.Shutdown();
    RendererSubsystem.Shutdown();
}

GEntity* CGameEngine::CreateEntity(const std::string& name) const
{
    GEntity* newEntity = Instance().NewObject<GEntity>();
    newEntity->SetName(name);
    CurrentScene->AddEntity(newEntity);
    return newEntity;
}

void CGameEngine::DestroyEntity(GEntity* entity) const
{
    CurrentScene->RemoveEntity(entity);
    Instance().FreeObject(entity);
}