#pragma once
#include "Window.h"
#include "../Game/Entity.h"
#include "../Game/Component.h"

class EInspectorWindow : public IWindow
{
public:
    EInspectorWindow() = default;
    ~EInspectorWindow() = default;

    const char* GetWindowName() const override { return "Inspector##InspectorWindow"; }

    void Render() override;

private:
    void RenderEntityProperties(GEntity* entity);
    void RenderComponentList(GEntity* entity);
    void RenderAddComponentPopup(GEntity* entity);
    void RenderComponent(GComponent* component);
    void RenderProperty(GComponent* component, const FProperty& prop);
    bool FuzzyMatch(const char* pattern, const char* text);

    bool bShowAddComponentPopup = false;
    char ComponentSearchBuffer[64] = "";
    GComponent* ComponentToDelete = nullptr;
};
