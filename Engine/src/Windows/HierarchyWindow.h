#pragma once
#include "Window.h"
#include "../Game/Entity.h"

class EHierarchyWindow : public IWindow
{
public:
    EHierarchyWindow() = default;
    ~EHierarchyWindow() = default;

    const char* GetWindowName() const override { return "Hierarchy##HierarchyWindow"; }

    void Render() override;
    
private:
    void RenderEntityNode(GEntity* entity);
    void RenderSelectEntityPopup();
    void RenderCreateEntityPopup();
    bool NameExists(const std::vector<GEntity*>& entities, const std::string& name);
    void MakeUniqueName(char* outName, size_t outNameSize, const char* baseName, const std::vector<GEntity*>& entities);
    bool FuzzyMatch(const char* pattern, const char* text);
   
    bool bShowSelectEntityPopup = false;
    bool bShowCreatePopup = false;
    char NewEntityName[64] = "Entity";
    char EntitySearchBuffer[64] = "";
    CClass* SelectedEntityType = nullptr;
};
