#pragma once
#ifndef CRENDER_SUBSYSTEM_H
#define CRENDER_SUBSYSTEM_H
#include <string>

#include "Subsystem.h"
#include "../Game/Entity.h"
#include "../Structs/Vectors.h"
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

    void OnBeginFrame() const;
    void OnEndFrame() const;

    SDL_Window* GetWindow() const { return window; }
    SDL_GLContext GetGLContext() const { return glContext; }

    void SetClearColor(FColor color) { ClearColor = color; }
    
private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext;

    FColor ClearColor;
};

#endif