#pragma once

#include "Subsystem.h"
#include "../Game/Entity.h"
#include "../Windows/WindowManager.h"
#include "../Windows/DebugWindow.h"
#include "../Windows/HierarchyWindow.h"
#include "../Windows/InspectorWindow.h"
#include "../Windows/WorkspaceWindow.h"
#include "../Windows/ConsoleWindow.h"

enum EEditorMode
{
    Editor,
    Play,
    Pause
};

inline const char* GetEditorModeName(EEditorMode mode)
{
    switch (mode)
    {
        case Editor: return "Editor";
        case Play: return "Play";
        case Pause: return "Pause";
        default: return "Unknown";
    }
}

class CEditorSubsystem : public ISubsystem
{
public:
    CEditorSubsystem() = default;
    ~CEditorSubsystem() = default;
    
    void Start() override;
    void Shutdown() override;
    void Update(float deltaSeconds) override;
    void Render() const;
    
    GEntity* GetSelectedEntity() const { return SelectedEntity; }
    void SetSelectedEntity(GEntity* entity) { SelectedEntity = entity; }
    
    CWindowManager& GetWindowManager() { return *WindowManager; }

    EEditorMode* GetEditorMode() const { return EditorMode; }
    void EnterPlayMode();
    void EnterPauseMode();
    void ExitPlayMode();
   
private:
    void SetEditorMode(EEditorMode mode)
    {
        *EditorMode = mode;
        SDL_Log("Editor mode: %s", GetEditorModeName(*EditorMode));
    }
    
    GEntity* SelectedEntity;
    CWindowManager* WindowManager;
    EEditorMode* EditorMode = nullptr;
};
