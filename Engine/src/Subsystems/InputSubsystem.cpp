#include "InputSubsystem.h"

#include <imgui_impl_sdl3.h>

#include "../Core/GameEngine.h"

void CInputSubsystem::Start()
{
    ButtonStates.fill(EButtonState::UP);
}

void CInputSubsystem::Shutdown() {}

void CInputSubsystem::Update(float deltaSeconds)
{
    for (auto& state : ButtonStates)
    {
        switch (state)
        {
            case EButtonState::PRESSED:
                state = EButtonState::DOWN;
                break;
            case EButtonState::RELEASED:
                state = EButtonState::UP;
                break;
            default:
                break;
        }
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        
        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            CGameEngine::Instance().Quit();

        if (event.type == SDL_EVENT_KEY_DOWN && !ImGui::GetIO().WantCaptureKeyboard)
            PendingPressedKeys.push_back(event.key.scancode);
        else if (event.type == SDL_EVENT_KEY_UP && !ImGui::GetIO().WantCaptureKeyboard)
            ButtonStates[event.key.scancode] = EButtonState::RELEASED;
    }
    
    for (SDL_Scancode key : PendingPressedKeys)
    {
        if (ButtonStates[key] == EButtonState::UP)
            ButtonStates[key] = EButtonState::PRESSED;
    }

    PendingPressedKeys.clear();
}

EButtonState CInputSubsystem::GetButtonState(SDL_Scancode key) const
{
    return ButtonStates[key];
}

bool CInputSubsystem::GetKeyDown(SDL_Scancode key)
{
    return CGameEngine::Instance().GetInput().GetButtonState(key) == EButtonState::DOWN;
}

bool CInputSubsystem::GetKeyUp(SDL_Scancode key)
{
    return CGameEngine::Instance().GetInput().GetButtonState(key) == EButtonState::UP;
}

bool CInputSubsystem::GetKeyPressed(SDL_Scancode key)
{
    return CGameEngine::Instance().GetInput().GetButtonState(key) == EButtonState::PRESSED;
}

bool CInputSubsystem::GetKeyReleased(SDL_Scancode key)
{
    return CGameEngine::Instance().GetInput().GetButtonState(key) == EButtonState::RELEASED;
}
