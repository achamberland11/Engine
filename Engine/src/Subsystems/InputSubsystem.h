#pragma once

#include <vector>
#include <array>

#include "Subsystem.h"
#include "SDL3/SDL_init.h"

enum class EButtonState
{
    UP, 
    DOWN, 
    PRESSED,
    RELEASED
};

class CInputSubsystem : public ISubsystem
{
public:
    CInputSubsystem() = default;
    ~CInputSubsystem() = default;

    void Start() override;
    void Shutdown() override;
    void Update(float deltaSeconds) override;

    EButtonState GetButtonState(SDL_Scancode key) const;

private:
    std::array<EButtonState, SDL_SCANCODE_COUNT> ButtonStates;
    std::vector<SDL_Scancode> PendingPressedKeys;
};
