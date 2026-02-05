#include "InputSubsystem.h"

void CInputSubsystem::Start() {}

void CInputSubsystem::Shutdown() {}

void CInputSubsystem::Update(float deltaSeconds)
{
    for (auto& pair : buttonStates)
    {
        EButtonState& state = pair.second;
        if (state == EButtonState::JUST_PRESSED)
            state = EButtonState::DOWN;
    }

    for (SDL_Keycode key : pendingPressedKeys)
    {
        if (buttonStates[key] == EButtonState::UP)
            buttonStates[key] = EButtonState::JUST_PRESSED;
    }

    pendingPressedKeys.clear();
}

SDL_AppResult CInputSubsystem::HandleEvent(SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    if (event->type == SDL_EVENT_KEY_DOWN)
        pendingPressedKeys.push_back(event->key.key);
    else if (event->type == SDL_EVENT_KEY_UP)
        buttonStates[event->key.key] = EButtonState::UP;
    
    return SDL_APP_CONTINUE;
}

EButtonState CInputSubsystem::GetButtonState(SDL_Keycode key) const
{
    auto it = buttonStates.find(key);
    return it != buttonStates.end() ? it->second : EButtonState::UP;
}
