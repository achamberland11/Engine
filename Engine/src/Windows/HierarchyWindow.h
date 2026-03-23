#pragma once
#include "Window.h"
#include "../Game/Entity.h"

class CEditorSubsystem;

class CHierarchyWindow : public IWindow
{
public:
    CHierarchyWindow() = default;
    ~CHierarchyWindow() = default;

    const char* GetWindowName() const override { return "Hierarchy##HierarchyWindow"; }

    void Render() override;
    
private:
    void RenderEntityNode(GEntity* entity);
    void RenderCreateEntityPopup();
    
    bool bShowCreatePopup = false;
    char NewEntityName[64] = "New Entity";
};
