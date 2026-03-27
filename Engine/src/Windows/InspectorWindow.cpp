#include "InspectorWindow.h"
#include <imgui.h>
#include <cctype>
#include <iostream>
#include <ostream>

#include "../Subsystems/EditorSubsystem.h"
#include "../Core/GameEngine.h"
#include "../Game/Components/ComponentRegistry.h"

void EInspectorWindow::Render()
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

void EInspectorWindow::RenderEntityProperties(GEntity* entity)
{
    ImGui::Text("Entity: %s", entity->GetName().c_str());
    ImGui::Checkbox("Active", entity->Active());
}

void EInspectorWindow::RenderComponentList(GEntity* entity)
{
    ImGui::Text("Components");

    std::vector<GComponent*> components = entity->GetComponents();
    for (GComponent* component : components)
    {
        ImGui::PushID(component);

        ImGui::AlignTextToFramePadding();
        bool isOpen = ImGui::TreeNodeEx(component->GetClass()->DisplayName.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth);


        if (component->GetClass()->bCanBeDeleted || component->GetClass()->bCanDuplicate)
        {
            if (ImGui::BeginPopupContextItem())
            {
                if (component->GetClass()->bCanBeDeleted)
                {
                    if (ImGui::MenuItem("Delete") && component->GetClass()->bCanBeDeleted)
                    {
                        ComponentToDelete = component;
                    }
                }

                if (component->GetClass()->bCanDuplicate)
                {
                    if (ImGui::MenuItem("Duplicate"))
                    {
                        component->GetClass()->Factory(entity, component->GetName());
                    }
                }
                ImGui::EndPopup();
            }
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
        ComponentToDelete = nullptr;
    }
}

void EInspectorWindow::RenderAddComponentPopup(GEntity* entity)
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
            if (!compClass->bCanDuplicate)
            {
                bool bExists = false;
                for (GComponent* component : entity->GetComponents())
                {
                    if (component->GetClass() == compClass)
                    {
                        bExists = true;
                        break;
                    }
                }
                if (bExists) continue;
            }
            if (ComponentSearchBuffer[0] != '\0' &&
                !FuzzyMatch(ComponentSearchBuffer, compClass->DisplayName.c_str()))
            {
                continue;
            }

            if (ImGui::Selectable(compClass->DisplayName.c_str()))
            {
                if (compClass->Factory)
                {
                    compClass->Factory(entity, compClass->GetName());
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

void EInspectorWindow::RenderComponent(GComponent* component)
{
    const auto& properties = component->GetClass()->Properties;
    for (const FProperty& prop : properties)
    {
        RenderProperty(component, prop);
    }
}

void EInspectorWindow::RenderProperty(GComponent* component, const FProperty& prop)
{
    void* ptr = reinterpret_cast<char*>(component) + prop.Offset;
    if (!component->GetClass()->bCanBeDisabled && prop.Name == "Enabled")
    {
        return;
    }
    prop.RenderProperty(ptr);
}

bool EInspectorWindow::FuzzyMatch(const char* pattern, const char* text)
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
