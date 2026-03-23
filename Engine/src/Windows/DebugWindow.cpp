#include "DebugWindow.h"
#include <imgui.h>

void CDebugWindow::Render()
{
    ImGui::SetNextWindowBgAlpha(0.5f);
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    
    if (ImGui::Begin("Debug##DebugOverlay", nullptr, GetFlags()))
    {
        ImGui::Text("FPS: %.1f", FPS);
        ImGui::Text("Frame Time: %.2f ms", FrameTime * 1000.0f);
        
        // ImGui::TextColored(ImColor {255, 255, 0,1}, "Memory");
        ImGui::Text("Memory Usage: %.2f MB / %.2f MB", 
            static_cast<float>(MemoryUsed),
            static_cast<float>(MemoryReserved));
        ImGui::Text("Used pages: %d", PageUsed);
        ImGui::Text("Pages available: %d", PageReserved);
        ImGui::Text("Page size: %d", PageSize);
        ImGui::Text("Total pages: %d", NbrPages);
    }
    ImGui::End();
}