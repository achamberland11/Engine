#include "DebugWindow.h"
#include <imgui.h>

void CDebugWindow::Render()
{
    ImGui::SetNextWindowBgAlpha(0.5f);
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);

    if (ImGui::Begin("Debug##DebugOverlay", nullptr, GetFlags()))
    {
        ImGui::SeparatorText("Performance");

        ImGui::Text("FPS: %.1f", FPS);
        ImGui::Text("Frame Time: %.2f ms", FrameTime * 1000.0f);

        ImGui::SeparatorText("Memory Usage");

        ImGui::Text("Memory Usage: %.2f KB / %.2f KB",
                    static_cast<float>(MemoryUsed) / 1024,
                    static_cast<float>(MemorySize) / 1024);
        ImGui::Text("Memory available: %.2f KB", static_cast<float>(MemoryReserved) / 1024);
        
        ImGui::SeparatorText("Allocator Pool");

        ImGui::Text("Used pages: %d", PageUsed);
        ImGui::Text("Pages available: %d", PageReserved);
        ImGui::Text("Page size: %d", PageSize);
        ImGui::Text("Total pages: %d", NbrPages);
    }

    ImGui::End();
}
