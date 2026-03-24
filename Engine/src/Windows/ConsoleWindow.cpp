#include "ConsoleWindow.h"

void CConsoleWindow::Render()
{
    if (ImGui::Begin(GetWindowName(), nullptr, GetFlags()))
    {
    }

    ImGui::End();
}
