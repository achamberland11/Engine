#include "DebugWindow.h"
#include <imgui.h>

void EDebugWindow::Render()
{
    ImGui::SetNextWindowBgAlpha(0.5f);
    ImGui::SetNextWindowPos(ImVec2(10, 110), ImGuiCond_Always);

    if (ImGui::Begin("Debug##DebugOverlay", nullptr, GetFlags()))
    {
        if (ImGui::CollapsingHeader("Debug  "))
        {
            ImGui::SeparatorText("Performance");
            if (ImGui::CollapsingHeader("Performance"))
            {
                ImGui::Text("FPS: %.1f", FPS);
                ImGui::Text("Frame Time: %.2f ms", FrameTime * 1000.0f);
            }

            ImGui::SeparatorText("Memory Usage");
            if (ImGui::CollapsingHeader("Memory Usage"))
            {
                ImGui::Text("Memory Usage: %.2f KB / %.2f KB",
                            static_cast<float>(MemoryUsed) / 1024,
                            static_cast<float>(MemorySize) / 1024);
                ImGui::Text("Memory available: %.2f KB", static_cast<float>(MemoryReserved) / 1024);
            }

            ImGui::SeparatorText("Allocator Pool");
            if (ImGui::CollapsingHeader("Allocator Pool"))
            {
                ImGui::Text("Used pages: %d", PageUsed);
                ImGui::Text("Pages available: %d", PageReserved);
                ImGui::Text("Page size: %d", PageSize);
                ImGui::Text("Total pages: %d", NbrPages);
            }
            
            ImGui::SeparatorText("Threading");
            if (ImGui::CollapsingHeader("Threading"))
            {
                if (ImGui::Button("Start Thread"))
                {
                    PrimeWorkerPtr->StartWorker();
                }
                ImGui::SameLine();
                if (ImGui::Button("Stop Thread"))
                {
                    PrimeWorkerPtr->StopWorker();
                }

                ImGui::Text("Found: %zu primes", DisplayedPrimes->size());
                if (ImGui::CollapsingHeader("Prime Numbers"))
                {
                    size_t sizeLimit = 25;
                    for (size_t i = 0; i < DisplayedPrimes->size() && i < sizeLimit; i++)
                    {
                        ImGui::Text("%d", (*DisplayedPrimes)[i]);
                    }
                    if (DisplayedPrimes->size() > sizeLimit)
                    {
                        ImGui::Text("... and %zu more", DisplayedPrimes->size() - sizeLimit);
                    }
                }
            }
        }
    }

    ImGui::End();
}
