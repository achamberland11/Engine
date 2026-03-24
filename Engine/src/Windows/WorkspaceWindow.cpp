#include "WorkspaceWindow.h"

#include <imgui_internal.h>

void CWorkspaceWindow::Render()
{
    if (ImGui::Begin(GetWindowName(), nullptr, GetFlags()))
    {

    }
    
    ImGui::End();
}