#include "InputSubsystem.h"

#include <imgui_impl_sdl3.h>

#include "../Core/GameEngine.h"

void CInputSubsystem::Start() {}

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
            PendingPressedKeys.push_back(event.key.key);
        else if (event.type == SDL_EVENT_KEY_UP && !ImGui::GetIO().WantCaptureKeyboard)
            ButtonStates[event.key.key] = EButtonState::UP;
    }
    
    for (auto& pair : ButtonStates)
    {
        EButtonState& state = pair.second;
        if (state == EButtonState::JUST_PRESSED)
            state = EButtonState::DOWN;
    }

    for (SDL_Keycode key : PendingPressedKeys)
    {
        if (ButtonStates[key] == EButtonState::UP)
            ButtonStates[key] = EButtonState::JUST_PRESSED;
    }

    PendingPressedKeys.clear();
}

EButtonState CInputSubsystem::GetButtonState(SDL_Keycode key) const
{
    auto it = ButtonStates.find(key);
    return it != ButtonStates.end() ? it->second : EButtonState::UP;
}
