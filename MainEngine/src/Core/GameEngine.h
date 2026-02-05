#pragma once
#include <mutex>

#include "Counter.h"
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

    CRendererSubsystem& GetRenderer() { return rendererSubsystem; }
    CInputSubsystem& GetInput() { return inputSubsystem; }
    CGameSubsystem& GetGame() { return gameSubsystem; }

private:
    CGameEngine() = default;
    ~CGameEngine() = default;

    CRendererSubsystem rendererSubsystem;
    CInputSubsystem inputSubsystem;
    CGameSubsystem gameSubsystem;
    CCounter counter;
};
