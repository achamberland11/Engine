#pragma once
#include <mutex>

#include "Counter.h"
#include "../Memory/PageAllocator.hpp"
#include "../Subsystems/GameSubsystem.h"
#include "../Subsystems/InputSubsystem.h"
#include "../Subsystems/RendererSubsystem.h"

class CGameEngine
{
private:
    CPageAllocator<128, 1024 * 1024> Allocator;
    
public:
    static CGameEngine& Instance()
    {
        static CGameEngine instance;
        return instance;
    }

    CGameEngine(const CGameEngine&) = delete;
    CGameEngine& operator=(const CGameEngine&) = delete;
    CGameEngine(CGameEngine&&) = delete;
    CGameEngine& operator=(CGameEngine&&) = delete;
    
    void Init();
    void Loop();
    void Shutdown();
    void Quit() { bShouldQuit = true; }
    bool ShouldQuit() const { return bShouldQuit; }

    CRendererSubsystem& GetRenderer() { return rendererSubsystem; }
    CInputSubsystem& GetInput() { return inputSubsystem; }
    CGameSubsystem& GetGame() { return gameSubsystem; }

    template <typename T> T* NewObject() { return Allocator.NewObject<T>(); }
    template <typename T> void FreeObject(T* InObject) { Allocator.FreeObject(InObject); }

    CPageAllocator<128, 1024 * 1024>& GetAllocator() { return Allocator; }

private:
    CGameEngine() = default;
    ~CGameEngine() = default;

    CRendererSubsystem rendererSubsystem;
    CInputSubsystem inputSubsystem;
    CGameSubsystem gameSubsystem;
    CCounter counter;

    bool bShouldQuit = false;
};
