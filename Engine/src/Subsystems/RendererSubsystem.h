#pragma once
#ifndef CRENDER_SUBSYSTEM_H
#define CRENDER_SUBSYSTEM_H
#include <string>

#include "Subsystem.h"
#include "../Game/Entity.h"
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

    void OnBeginFrame() const;
    void OnEndFrame() const;

    SDL_Window* GetWindow() const { return window; }
    SDL_GLContext GetGLContext() const { return glContext; }

    void SetFrameTimeText(const std::string& text) { frameText = text; }
    void SetFPSText(const std::string& text) { fpsText = text; }
    void SetClearColor(FColor color) { ClearColor = color; }
    
private:
    void RenderFPSCounterWindow() const;
    void RenderMemoryAllocatorWindow() const;
    void RenderEntityWindow() const;
    
    void RenderEntityCreation(char* entityName, size_t entityNameSize) const;
    void RenderEntityList(GEntity*& entityToDelete) const;
    void RenderEntityProperties(GEntity* entity) const;
    void RenderAddComponentPopup(GEntity* entity) const;
    void RenderComponentList(GEntity* entity, GComponent*& componentToDelete) const;
    void ShowComponentProperties(GComponent* component) const;

    static bool NameExists(const std::vector<GEntity*>& entities, const std::string& name);
    static void MakeUniqueName(char* outName, size_t outNameSize, const char* baseName, const std::vector<GEntity*>& entities);


    SDL_Window* window = nullptr;
    SDL_GLContext glContext;

    std::string frameText;
    std::string fpsText;
    FColor ClearColor;
};

#endif