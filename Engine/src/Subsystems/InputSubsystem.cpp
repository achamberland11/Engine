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
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        
        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            CGameEngine::Instance().Quit();

        if (event.type == SDL_EVENT_KEY_DOWN && !ImGui::GetIO().WantCaptureKeyboard)
            PendingPressedKeys.push_back(event.key.scancode);
        else if (event.type == SDL_EVENT_KEY_UP && !ImGui::GetIO().WantCaptureKeyboard)
            ButtonStates[event.key.scancode] = EButtonState::UP;
    }
    
    for (auto& state : ButtonStates)
    {
        if (state == EButtonState::JUST_PRESSED)
            state = EButtonState::DOWN;
    }

    for (SDL_Scancode key : PendingPressedKeys)
    {
        if (ButtonStates[key] == EButtonState::UP)
            ButtonStates[key] = EButtonState::JUST_PRESSED;
    }

    PendingPressedKeys.clear();
}

EButtonState CInputSubsystem::GetButtonState(SDL_Scancode key) const
{
    return ButtonStates[key];
}
