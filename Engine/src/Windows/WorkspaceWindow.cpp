#include "WorkspaceWindow.h"

#include <imgui_internal.h>

#include "../Core/GameEngine.h"
#include "SDL3/SDL_opengl.h"

void EWorkspaceWindow::Render()
{
    if (ImGui::Begin(GetWindowName(), nullptr, GetFlags()))
    {
        ImVec2 availableSize = ImGui::GetContentRegionAvail();
        
        GLuint sceneTexture = CGameEngine::Instance().GetRenderer().GetSceneTexture();
        
        ImGui::Image(
            sceneTexture,
            availableSize,
            ImVec2(0, 1),
            ImVec2(1, 0)
        );
    }
    
    ImGui::End();
}
