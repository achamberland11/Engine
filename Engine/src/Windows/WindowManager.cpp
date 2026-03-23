#include "WindowManager.h"

void CWindowManager::RenderWindows()
{
    for (auto& window : Windows)
    {
        window->Render();
    }
}

void CWindowManager::SaveLayout()
{
    ImGui::SaveIniSettingsToDisk("layout.ini");
}

void CWindowManager::LoadLayout()
{
    ImGui::LoadIniSettingsFromDisk("layout.ini");
}
