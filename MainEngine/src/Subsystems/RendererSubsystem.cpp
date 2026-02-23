#include "RendererSubsystem.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "../Core/GameEngine.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_opengl.h"

void CRendererSubsystem::Start()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        SDL_Log("Error: SDL_Init(): %s", SDL_GetError());
        return;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); 

    float scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    window = SDL_CreateWindow("Main Engine", (int)(1280 * scale), (int)(800 * scale), window_flags);

    if (!window)
    {
        SDL_Log("Error: SDL_CreateWindow(): %s", SDL_GetError());
        CGameEngine::Instance().Quit();
        return;
    }

    glContext = SDL_GL_CreateContext(window);

    if (!glContext)
    {
        SDL_Log("Error: SDL_GL_CreateContext(): %s", SDL_GetError());
        CGameEngine::Instance().Quit();
        return;
    }

    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(1);
    SDL_ShowWindow(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();
    
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void CRendererSubsystem::Shutdown()
{
    if (glContext)
    {
        SDL_GL_DestroyContext(glContext);
        glContext = nullptr;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void CRendererSubsystem::Update(float deltaSeconds)
{
    Render();
}

void CRendererSubsystem::Render() const
{
    const char* fpsMessage = fpsText.c_str();
    const char* frameMessage = frameText.c_str();
    
    ImGui::Begin("Hello World");
    ImGui::Text("%s", fpsMessage);
    ImGui::Text("%s", frameMessage);
    ImGui::End();

    ImGui::Begin("Memory Allocator");
    ImGui::Text("Used pages: %d", CGameEngine::Instance().GetAllocator().GetUsedPages());
    ImGui::Text("Pages available: %d", CGameEngine::Instance().GetAllocator().GetAvailablePages());
    ImGui::Text("Total pages: %d", 1024 * 1024);
    ImGui::End();
}

void CRendererSubsystem::OnBeginFrame()
{
    glViewport(0, 0, 1280, 800);
    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void CRendererSubsystem::OnEndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
}
