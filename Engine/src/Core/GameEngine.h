#pragma once
#include <mutex>

#include "Counter.h"
#include "../Memory/PageAllocator.hpp"
#include "../Subsystems/GameSubsystem.h"
#include "../Subsystems/InputSubsystem.h"
#include "../Subsystems/RendererSubsystem.h"

class CGameEngine
{
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

    CRendererSubsystem& GetRenderer() { return RendererSubsystem; }
    CInputSubsystem& GetInput() { return InputSubsystem; }
    CGameSubsystem& GetGame() { return GameSubsystem; }

    template <typename T> T* NewObject() { return Allocator.NewObject<T>(); }
    template <typename T> void FreeObject(T* InObject) { Allocator.FreeObject(InObject); }

    CPageAllocator<128, 1024 * 1024>& GetAllocator() { return Allocator; }

private:
    CGameEngine() = default;
    ~CGameEngine() = default;

    CPageAllocator<128, 1024 * 1024> Allocator;
    
    CRendererSubsystem RendererSubsystem;
    CInputSubsystem InputSubsystem;
    CGameSubsystem GameSubsystem;
    CCounter Counter;

    bool bShouldQuit = false;
};
