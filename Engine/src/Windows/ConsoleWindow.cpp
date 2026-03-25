#include "ConsoleWindow.h"

void EConsoleWindow::Render()
{
    if (ImGui::Begin(GetWindowName(), nullptr, GetFlags()))
    {
    }

    ImGui::End();
}