#pragma once

#include "Subsystem.h"
#include "../Game/Entity.h"
#include "../Windows/WindowManager.h"
#include "../Windows/DebugWindow.h"
#include "../Windows/HierarchyWindow.h"
#include "../Windows/InspectorWindow.h"
#include "../Windows/WorkspaceWindow.h"
#include "../Windows/ConsoleWindow.h"

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
   
private:
    GEntity* SelectedEntity;
    CWindowManager* WindowManager;
};
