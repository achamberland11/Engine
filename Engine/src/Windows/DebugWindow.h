#pragma once
#include "../Windows/Window.h"

class CDebugWindow : public IWindow
{
public:
    CDebugWindow() { Title = "Debug"; }

    const char* GetWindowName() const override { return "Debug##DebugWindow"; }
    ImGuiWindowFlags GetFlags() const override
    {
        return /*ImGuiWindowFlags_NoDocking |*/ ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground |
               ImGuiWindowFlags_NoTitleBar;
    }
    bool ShouldBeDocked() const override { return false; }

    void SetFPS(float fps) { FPS = fps; }
    void SetFrameTime(float time) { FrameTime = time; }
    void SetMemoryUsage(int usedMemory, int reservedMemory, int usedPages, int reservedPages) { MemoryUsed = usedMemory; MemoryReserved = reservedMemory; PageUsed = usedPages; PageReserved = reservedPages; };
    void SetMemoryStats(int memorySize, int pageSize, int nbrPages) { MemorySize = memorySize; PageSize = pageSize; NbrPages = nbrPages; };
    void Render() override;
    
private:
    float FPS = 0.0f;
    float FrameTime = 0.0f;
    
    int PageUsed = 0;
    int PageReserved = 0;
    int MemorySize = 0;
    int MemoryUsed = 0;
    int MemoryReserved = 0;
    int PageSize = 0;
    int NbrPages = 0;
};
