#include "WorkspaceWindow.h"

#include <imgui_internal.h>

void EWorkspaceWindow::Render()
{
    if (ImGui::Begin(GetWindowName(), nullptr, GetFlags()))
    {

    }
    
    ImGui::End();
}