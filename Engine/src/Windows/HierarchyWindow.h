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
    bool NameExists(const std::vector<GEntity*>& entities, const std::string& name);
    void MakeUniqueName(char* outName, size_t outNameSize, const char* baseName, const std::vector<GEntity*>& entities);
    
    bool bShowCreatePopup = false;
    char NewEntityName[64] = "Entity";
};
