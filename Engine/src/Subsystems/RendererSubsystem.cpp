#include "RendererSubsystem.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "../Core/GameEngine.h"
#include "../Windows/WindowManager.h"
#include "../Windows/DebugWindow.h"
#include "../Windows/HierarchyWindow.h"
#include "../Windows/InspectorWindow.h"
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
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    }

    float scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    window = SDL_CreateWindow("Asimov Engine", (int)(ViewportSize.x * scale), (int)(ViewportSize.y * scale), window_flags);

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
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    
    SDL_GL_SetSwapInterval(1);
    SDL_ShowWindow(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 410");
    
    InitializeFrameBuffer(ViewportSize.x, ViewportSize.y);
}

void CRendererSubsystem::Shutdown()
{
    if (SceneTexture != 0)
    {
        glDeleteTextures(1, &SceneTexture);
        SceneTexture = 0;
    }
    
    if (DepthRenderBuffer != 0)
    {
        glDeleteRenderbuffers(1, &DepthRenderBuffer);
        DepthRenderBuffer = 0;
    }
    
    if (FrameBuffer != 0)
    {
        glDeleteFramebuffers(1, &FrameBuffer);
        FrameBuffer = 0;
    }
    
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
    RenderScene();
    CGameEngine::Instance().GetEditor().Render();
}

void CRendererSubsystem::RenderScene() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
    
    glViewport(0, 0, ViewportSize.x, ViewportSize.y);
    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    // TODO: Entity rendering
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CRendererSubsystem::OnBeginFrame() const
{
    FVector2i size;
    SDL_GetWindowSize(window, &size.x, &size.y);
    
    glViewport(0, 0, size.x, size.y);
    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DockSpace", nullptr, windowFlags);
    ImGui::PopStyleVar(3);

    ImGuiID dockspaceID = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();
}

void CRendererSubsystem::OnEndFrame() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
}

void CRendererSubsystem::InitializeFrameBuffer(int width, int height)
{
    glGenFramebuffers(1, &FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
    
    glGenTextures(1, &SceneTexture);
    glBindTexture(GL_TEXTURE_2D, SceneTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, SceneTexture, 0);
    
    glGenRenderbuffers(1, &DepthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, DepthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthRenderBuffer);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        SDL_Log("Error: Framebuffer is not complete!");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
