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

    ImGui::Begin("FPS Counter");
    ImGui::Text("%s", fpsMessage);
    ImGui::Text("%s", frameMessage);
    ImGui::End();

    ImGui::Begin("Memory Allocator");
    ImGui::Text("Used pages: %d", CGameEngine::Instance().GetAllocator().GetUsedPages());
    ImGui::Text("Pages available: %d", CGameEngine::Instance().GetAllocator().GetAvailablePages());
    ImGui::Text("Total pages: %d", 1024 * 1024);
    ImGui::End();

    ImGui::Begin("Entity Component System");
    static char entityName[128] = "NewEntity";
    static int entityID = 0;
    ImGui::InputText("Entity Name", entityName, IM_ARRAYSIZE(entityName));

    // @TODO Add push ID to entity creation with ImGUI
    if (ImGui::Button("Create Entity"))
    {
        bool bNameExists = false;
        for (const CEntity* entity : CGameEngine::Instance().GetGame().GetEntities())
        {
            if (entity->Name == entityName)
            {
                bNameExists = true;
                break;
            }
        }

        if (!bNameExists)
            CGameEngine::Instance().GetGame().CreateEntity(entityName);
        else
        {
            if (entityID == 1)
            {
                snprintf(entityName, sizeof(entityName), "NewEntity1");
            }
            else
            {
                snprintf(entityName, sizeof(entityName), "NewEntity%d", entityID);
            }
            entityID++;
            CGameEngine::Instance().GetGame().CreateEntity(entityName);
        }
    }

    ImGui::Separator();
    ImGui::Text("Entities:");

    for (CEntity* entity : CGameEngine::Instance().GetGame().GetEntities())
    {
        if (ImGui::CollapsingHeader(entity->Name.c_str()))
        {
            if (ImGui::Button("Delete Entity"))
            {
                CGameEngine::Instance().GetGame().DestroyEntity(entity);
                break;
            }
            
            ImGui::PushID(entity->Name.c_str());

            const std::vector<CProperty>* properties = entity->GetProperties();
            for (const CProperty& property : *properties)
            {
                if (property.Type == EPropertyType::String)
                {
                    std::string* stringPtr = reinterpret_cast<std::string*>(reinterpret_cast<char*>(entity) + property.
                        Offset);
                    char buffer[128];
                    strcpy_s(buffer, stringPtr->c_str());
                    if (ImGui::InputText(property.Name.c_str(), buffer, sizeof(buffer)))
                        *stringPtr = buffer;
                }
                else if (property.Type == EPropertyType::Bool)
                {
                    bool* boolPtr = reinterpret_cast<bool*>(reinterpret_cast<char*>(entity) + property.Offset);
                    ImGui::Checkbox(property.Name.c_str(), boolPtr);
                }
            }

            if (ImGui::Button("Add Component"))
            {
                // ImGui::OpenPopup("Add Component");
                // ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
                CComponent* newComponent = CGameEngine::Instance().NewObject<CComponent>();
                bool bComponentExists = false;
                for (const CComponent* component : entity->GetComponents())
                {
                    if (component->Name == newComponent->Name)
                    {
                        bComponentExists = true;
                        break;
                    }
                }
                if (!bComponentExists) entity->AddComponent(newComponent);
                else CGameEngine::Instance().FreeObject(newComponent);
            }

            ImGui::Text("Components:");
            for (CComponent* component : entity->GetComponents())
            {
                ImGui::BulletText(component->Name.c_str());
                if (ImGui::Button("Delete Component"))
                {
                    entity->RemoveComponent(component);
                    CGameEngine::Instance().FreeObject(component);
                }
            }
        }
    }

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
