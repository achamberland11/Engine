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
    void SetClearColor(Color color) { ClearColor = color; }
    
private:
    void RenderFPSCounterWindow() const;
    void RenderMemoryAllocatorWindow() const;
    void RenderEntityWindow() const;
    
    void RenderEntityCreation(char* entityName, size_t entityNameSize) const;
    void RenderEntityList(CEntity*& entityToDelete) const;
    void RenderEntityProperties(CEntity* entity) const;
    void RenderAddComponentPopup(CEntity* entity) const;
    void RenderComponentList(CEntity* entity, CComponent*& componentToDelete) const;
    void ShowComponentProperties(CComponent* component) const;

    static bool NameExists(const std::vector<CEntity*>& entities, const std::string& name);
    static void MakeUniqueName(char* outName, size_t outNameSize, const char* baseName, const std::vector<CEntity*>& entities);


    SDL_Window* window = nullptr;
    SDL_GLContext glContext;

    std::string frameText;
    std::string fpsText;
    Color ClearColor;
};

#endif