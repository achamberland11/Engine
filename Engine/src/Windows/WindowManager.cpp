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

IWindow* CWindowManager::GetWindowByName(const char* name) const
{
    for (auto& window : Windows)
    {
        if (strcmp(window->GetWindowName(), name) == 0)
        {
            return window.get();
        }
    }
    return nullptr;
}
