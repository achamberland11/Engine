#include "InspectorWindow.h"
#include <imgui.h>
#include <cctype>
#include "../Subsystems/EditorSubsystem.h"
#include "../Core/GameEngine.h"
#include "../Game/Components/ComponentRegistry.h"

// TODO: 5. Implement CInspectorWindow - full implementation
// - Display components and properties
// - Handle property editing
// - Component addition/deletion
void CInspectorWindow::Render()
{
    GEntity* selectedEntity = CGameEngine::Instance().GetEditor().GetSelectedEntity();

    if (ImGui::Begin("Inspector##InspectorWindow", nullptr, GetFlags()))
    {
        if (!selectedEntity)
        {
            ImGui::Text("No entity selected");
            ImGui::End();
            return;
        }

        ImGui::Separator();
        RenderEntityProperties(selectedEntity);
        ImGui::Separator();
        RenderComponentList(selectedEntity);
        RenderAddComponentPopup(selectedEntity);
    }

    ImGui::End();
}

void CInspectorWindow::RenderEntityProperties(GEntity* entity)
{
    ImGui::Text("Entity: %s", entity->Name.c_str());
    ImGui::Checkbox("Active", &entity->bActive);
}

void CInspectorWindow::RenderComponentList(GEntity* entity)
{
    ImGui::Text("Components");

    for (GComponent* component : entity->Components)
    {
        ImGui::PushID(component);

        ImGui::AlignTextToFramePadding();
        bool isOpen = ImGui::TreeNodeEx(component->GetClass()->DisplayName.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth);

        ImGui::SameLine(ImGui::GetWindowWidth() - 30);
        if (ImGui::Button("X", ImVec2(20, 20)))
        {
            ComponentToDelete = component;
        }

        if (isOpen)
        {
            RenderComponent(component);
            ImGui::TreePop();
        }

        ImGui::PopID();
    }

    if (ImGui::Button("+ Add Component"))
    {
        bShowAddComponentPopup = true;
        ComponentSearchBuffer[0] = '\0';
    }

    if (ComponentToDelete)
    {
        entity->RemoveComponent(ComponentToDelete);
        CGameEngine::Instance().FreeObject(ComponentToDelete);
        ComponentToDelete = nullptr;
    }
}

void CInspectorWindow::RenderAddComponentPopup(GEntity* entity)
{
    if (bShowAddComponentPopup)
    {
        ImGui::OpenPopup("Add Component");
        bShowAddComponentPopup = false;
    }

    if (ImGui::BeginPopupModal("Add Component", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Search", ComponentSearchBuffer, sizeof(ComponentSearchBuffer));
        ImGui::Separator();

        const auto& components = CComponentRegistry::Instance().GetAllComponents();
        for (CClass* compClass : components)
        {
            if (ComponentSearchBuffer[0] != '\0' &&
                !FuzzyMatch(ComponentSearchBuffer, compClass->DisplayName.c_str()))
            {
                continue;
            }

            if (ImGui::Selectable(compClass->DisplayName.c_str()))
            {
                if (compClass->Factory)
                {
                    compClass->Factory(entity);
                }
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::Separator();
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void CInspectorWindow::RenderComponent(GComponent* component)
{
    const auto& properties = component->GetClass()->Properties;
    for (const FProperty& prop : properties)
    {
        RenderProperty(component, prop);
    }
}

void CInspectorWindow::RenderProperty(GComponent* component, const FProperty& prop)
{
    void* ptr = reinterpret_cast<char*>(component) + prop.Offset;

    switch (prop.Type)
    {
    case EPropertyType::Int:
        ImGui::DragInt(prop.Name.c_str(), static_cast<int*>(ptr), 1.0f);
        break;
    case EPropertyType::Float:
        ImGui::DragFloat(prop.Name.c_str(), static_cast<float*>(ptr), 0.1f);
        break;
    case EPropertyType::Bool:
        ImGui::Checkbox(prop.Name.c_str(), static_cast<bool*>(ptr));
        break;
    /*case EPropertyType::String:
        ImGui::InputText(prop.Name.c_str(), static_cast<std::string*>(ptr));
        break;*/
    case EPropertyType::Vector2:
        ImGui::DragFloat2(prop.Name.c_str(), static_cast<float*>(ptr), 0.1f);
        break;
    case EPropertyType::Vector3:
        ImGui::DragFloat3(prop.Name.c_str(), static_cast<float*>(ptr), 0.1f);
        break;
    default:
        ImGui::Text("%s: (unsupported)", prop.Name.c_str());
        break;
    }
}

bool CInspectorWindow::FuzzyMatch(const char* pattern, const char* text)
{
    const char* patternPtr = pattern;
    const char* textPtr = text;

    while (*patternPtr && *textPtr)
    {
        if (tolower(*patternPtr) == tolower(*textPtr))
        {
            patternPtr++;
        }
        textPtr++;
    }

    return *patternPtr == '\0';
}
