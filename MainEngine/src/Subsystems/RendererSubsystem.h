#pragma once
#include <string>

#include "Subsystem.h"
#include "../Structs/Color.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

class CRendererSubsystem : public ISubsystem
{
public:
    ~CRendererSubsystem() = default;

    void Start() override;
    void Shutdown() override;
    void Update(float deltaSeconds) override;

    void SetFrameTimeText(const std::string& text) { FrameText = text; }
    void SetFPSText(const std::string& text) { fpsText = text; }
    void SetClearColor(Color color) { ClearColor = color; }

    SDL_Window* GetWindow() const { return window; }
    SDL_Renderer* GetRenderer() const { return renderer; }

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::string FrameText;
    std::string fpsText;
    Color ClearColor;
};
