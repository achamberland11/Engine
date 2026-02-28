#include "RendererSubsystem.h"

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "../Core/GameEngine.h"
#include "../Factories/ComponentFactory.hpp"
#include "../Game/Components/TransformComponent.h"
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
    RenderFPSCounterWindow();
    RenderMemoryAllocatorWindow();
    RenderEntityWindow();
}

void CRendererSubsystem::RenderFPSCounterWindow() const
{
    ImGui::Begin("FPS Counter");
    ImGui::Text("%s", fpsText.c_str());
    ImGui::Text("%s", frameText.c_str());
    ImGui::End();
}

void CRendererSubsystem::RenderMemoryAllocatorWindow() const
{
    ImGui::Begin("Memory Allocator");
    ImGui::Text("Used pages: %d", CGameEngine::Instance().GetAllocator().GetUsedPages());
    ImGui::Text("Pages available: %d", CGameEngine::Instance().GetAllocator().GetAvailablePages());
    ImGui::Text("Total pages: %d", 1024 * 1024);
    ImGui::End();
}

void CRendererSubsystem::RenderEntityWindow() const
{
    ImGui::Begin("Entity Component System");

    static char entityName[128] = "NewEntity";
    RenderEntityCreation(entityName, sizeof(entityName));

    ImGui::Separator();
    ImGui::Text("Entities:");

    CEntity* entityToDelete = nullptr;
    RenderEntityList(entityToDelete);

    if (entityToDelete)
    {
        CGameEngine::Instance().GetGame().DestroyEntity(entityToDelete);
        CGameEngine::Instance().FreeObject(entityToDelete);
    }

    ImGui::End();
}

void CRendererSubsystem::RenderEntityCreation(char* entityName, size_t entityNameSize) const
{
    ImGui::InputText("Entity Name", entityName, entityNameSize);

    if (ImGui::Button("Create Entity"))
    {
        char baseName[128];
        strcpy_s(baseName, entityName);

        auto& entities = CGameEngine::Instance().GetGame().GetEntities();

        MakeUniqueName(entityName, entityNameSize, baseName, entities);
        CGameEngine::Instance().GetGame().CreateEntity(entityName);
        std::snprintf(entityName, entityNameSize, "NewEntity");
    }
}

void CRendererSubsystem::RenderEntityList(CEntity*& entityToDelete) const
{
    for (CEntity* entity : CGameEngine::Instance().GetGame().GetEntities())
    {
        ImGui::PushID(entity);
        if (ImGui::CollapsingHeader(entity->Name.c_str()))
        {
            if (ImGui::Button("Delete Entity"))
            {
                entityToDelete = entity;
            }

            RenderEntityProperties(entity);
            RenderAddComponentPopup(entity);

            CComponent* componentToDelete = nullptr;
            RenderComponentList(entity, componentToDelete);

            if (componentToDelete)
            {
                entity->RemoveComponent(componentToDelete);
                CGameEngine::Instance().FreeObject(componentToDelete);
            }
        }

        ImGui::PopID();

        if (entityToDelete)
            break;
    }
}

void CRendererSubsystem::RenderEntityProperties(CEntity* entity) const
{
    const std::vector<CProperty>* properties = entity->GetProperties();
    for (const CProperty& property : *properties)
    {
        if (property.Type == EPropertyType::String)
        {
            std::string* stringPtr = reinterpret_cast<std::string*>(reinterpret_cast<char*>(entity) + property.Offset);
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
}

void CRendererSubsystem::RenderAddComponentPopup(CEntity* entity) const
{
    static ComponentFactory compFactory;

    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("Add Component Popup");
    }

    if (ImGui::BeginPopup("Add Component Popup"))
    {
        if (ImGui::Selectable("Transform"))
        {
            compFactory.NewComponent<CTransformComponent>(entity);
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void CRendererSubsystem::RenderComponentList(CEntity* entity, CComponent*& componentToDelete) const
{
    for (CComponent* component : entity->GetComponents())
    {
        ImGui::PushID(component);
        if (ImGui::CollapsingHeader(component->Name.c_str()))
        {
            ShowComponentProperties(component);
            if (ImGui::Button("Delete Component"))
            {
                componentToDelete = component;
            }
        }

        ImGui::PopID();

        if (componentToDelete)
            break;
    }
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

bool CRendererSubsystem::NameExists(const std::vector<CEntity*>& entities, const std::string& name)
{
    for (const CEntity* entity : entities)
    {
        if (entity->Name == name)
            return true;
    }
    return false;
}

void CRendererSubsystem::MakeUniqueName(char* outName, size_t outNameSize, const char* baseName,
                                        const std::vector<CEntity*>& entities)
{
    if (!NameExists(entities, baseName))
    {
        std::snprintf(outName, outNameSize, "%s", baseName);
        return;
    }

    for (int i = 0; i < 10000000; ++i)
    {
        std::snprintf(outName, outNameSize, "%s_%d", baseName, i);

        if (!NameExists(entities, outName))
            return;
    }

    std::snprintf(outName, outNameSize, "%s", "X");
}

void CRendererSubsystem::ShowComponentProperties(CComponent* component) const
{
}
