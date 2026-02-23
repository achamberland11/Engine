#pragma once
#ifndef CRENDER_SUBSYSTEM_H
#define CRENDER_SUBSYSTEM_H
#include <string>

#include "Subsystem.h"
#include "../Structs/Color.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

class CRendererSubsystem : public ISubsystem
{
public:
    CRendererSubsystem() = default;
    ~CRendererSubsystem() = default;

    void Start() override;
    void Shutdown() override;
    void Update(float deltaSeconds) override;
    void Render() const;

    void OnBeginFrame();
    void OnEndFrame();

    SDL_Window* GetWindow() const { return window; }
    SDL_GLContext GetGLContext() const { return glContext; }

    void SetFrameTimeText(const std::string& text) { frameText = text; }
    void SetFPSText(const std::string& text) { fpsText = text; }
    void SetClearColor(Color color) { ClearColor = color; }

private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext;

    std::string frameText;
    std::string fpsText;
    Color ClearColor;
};

#endif