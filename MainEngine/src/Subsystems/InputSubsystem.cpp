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
            pendingPressedKeys.push_back(event.key.key);
        else if (event.type == SDL_EVENT_KEY_UP && !ImGui::GetIO().WantCaptureKeyboard)
            buttonStates[event.key.key] = EButtonState::UP;
    }
    
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

EButtonState CInputSubsystem::GetButtonState(SDL_Keycode key) const
{
    auto it = buttonStates.find(key);
    return it != buttonStates.end() ? it->second : EButtonState::UP;
}
