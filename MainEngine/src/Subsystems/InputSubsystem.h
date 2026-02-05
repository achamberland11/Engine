#pragma once
#include <unordered_map>

#include "Subsystem.h"
#include "SDL3/SDL_init.h"

enum class EButtonState { UP, DOWN, JUST_PRESSED };

class CInputSubsystem : public ISubsystem
{
public:
    ~CInputSubsystem() = default;

    void Start() override;
    void Shutdown() override;
    void Update(float deltaSeconds) override;

    SDL_AppResult HandleEvent(SDL_Event* event);
    EButtonState GetButtonState(SDL_Keycode key) const;

private:
    std::unordered_map<SDL_Keycode, EButtonState> buttonStates;
    std::vector<SDL_Keycode> pendingPressedKeys;
};
