#include "ToolbarWindow.h"
#include "imgui.h"
#include "SDL3/SDL_dialog.h"
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_log.h"
#include "../Core/GameEngine.h"
#include "../Core/Scene.h"
#include <filesystem>

std::string EToolbarWindow::LastSaveDirectory = "../Game/Assets/";

static void SaveFileCallback(void* userdata, const char* const* filepaths, int filetype)
{
    if (filepaths && filepaths[0])
    {
        std::string selectedPath = filepaths[0];
        
        if (!selectedPath.ends_with(".json"))
        {
            selectedPath += ".json";
        }
        
        CScene* scene = CGameEngine::Instance().GetCurrentScene();
        if (scene)
        {
            bool success = scene->SaveToFile(selectedPath);
            if (success)
            {
                std::filesystem::path path(selectedPath);
                EToolbarWindow::SetLastSaveDirectory(path.parent_path().string());
                SDL_Log("Scene saved to: %s", selectedPath.c_str());
            }
            else
            {
                SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to save scene to: %s", selectedPath.c_str());
            }
        }
    }
}

static void OpenFileCallback(void* userdata, const char* const* filepaths, int filetype)
{
    if (filepaths && filepaths[0])
    {
        std::string selectedPath = filepaths[0];
        CScene* scene = CGameEngine::Instance().GetCurrentScene();
        if (scene)
        {
            bool success = scene->LoadFromFile(selectedPath);
            if (success)
            {
                std::filesystem::path path(selectedPath);
                EToolbarWindow::SetLastSaveDirectory(path.parent_path().string());
                SDL_Log("Scene loaded from: %s", selectedPath.c_str());
            }
            else
            {
                SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load scene from: %s", selectedPath.c_str());
            }
        }
    }
}

void EToolbarWindow::Render()
{
    if (ImGui::Begin(GetWindowName(), nullptr, GetFlags()))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, 4.0f));
        
        if (ImGui::Button("New Scene"))
        {
            NewScene();
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Save"))
        {
            SaveScene();
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Open"))
        {
            OpenScene();
        }
        
        ImGui::SameLine();
        
        RenderSceneInfo();
        
        ImGui::PopStyleVar();
    }
    
    ImGui::End();
}

void EToolbarWindow::NewScene()
{
    CScene* scene = CGameEngine::Instance().GetCurrentScene();
    if (scene)
    {
        scene->Clear();
        scene->SetCurrentScenePath("");
        SDL_Log("New scene created");
    }
}

void EToolbarWindow::SaveScene()
{
    CScene* scene = CGameEngine::Instance().GetCurrentScene();
    if (!scene) return;
    
    std::string defaultPath = LastSaveDirectory;
    
    std::string suggestedName = "scene.json";
    if (!scene->GetCurrentScenePath().empty())
    {
        std::filesystem::path currentPath(scene->GetCurrentScenePath());
        suggestedName = currentPath.filename().string();
        if (!suggestedName.ends_with(".json"))
        {
            suggestedName += ".json";
        }
    }
    
    defaultPath += suggestedName;
    
    SDL_DialogFileFilter filters[] = {
        { "Scene files", "json" },
        { "All files", "*" }
    };
    
    SDL_ShowSaveFileDialog(
        SaveFileCallback,
        nullptr,
        nullptr,
        filters,
        2,
        defaultPath.c_str()
    );
}

void EToolbarWindow::OpenScene()
{
    const char* defaultPath = LastSaveDirectory.c_str();
    
    SDL_DialogFileFilter filters[] = {
        { "Scene files", "json" },
        { "All files", "*" }
    };
    
    SDL_ShowOpenFileDialog(
        OpenFileCallback,
        nullptr,
        nullptr,
        filters,
        2,
        defaultPath,
        false
    );
}

void EToolbarWindow::RenderSceneInfo()
{
    CScene* scene = CGameEngine::Instance().GetCurrentScene();
    if (!scene) return;
    
    std::string scenePath = scene->GetCurrentScenePath();
    
    ImGui::SameLine();
    ImGui::TextUnformatted("|");
    ImGui::SameLine();
    
    if (scenePath.empty())
    {
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Unsaved Scene");
    }
    else
    {
        std::filesystem::path path(scenePath);
        ImGui::Text("%s", path.filename().string().c_str());
    }
}
