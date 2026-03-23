#include "HierarchyWindow.h"
#include <imgui.h>
#include "../Subsystems/EditorSubsystem.h"
#include "../Core/GameEngine.h"
#include "HierarchyWindow.h"

// TODO: 4. Implement CHierarchyWindow - full implementation
// - Entities visualization
// - Parenting support
// - Drag and drop
// - Creation/Deletion
void CHierarchyWindow::Render()
{
    if (ImGui::Button("+ Create Entity"))
    {
        bShowCreatePopup = true;
    }
    ImGui::Separator();

    const auto& entities = CGameEngine::Instance().GetGame().GetEntities();
    for (GEntity* entity : entities)
    {
        if (entity->Parent == nullptr)
        {
            RenderEntityNode(entity);
        }
    }

    RenderCreateEntityPopup();
}

void CHierarchyWindow::RenderEntityNode(GEntity* entity)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    
    if (CGameEngine::Instance().GetEditor().GetSelectedEntity() == entity)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }
    
    if (entity->Children.empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    bool isOpen = ImGui::TreeNodeEx(entity->Name.c_str(), flags);
    
    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    {
        CGameEngine::Instance().GetEditor().SetSelectedEntity(entity);
    }

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Delete"))
        {
            CGameEngine::Instance().GetGame().DestroyEntity(entity);
            if (CGameEngine::Instance().GetEditor().GetSelectedEntity() == entity)
            {
                CGameEngine::Instance().GetEditor().SetSelectedEntity(nullptr);
            }
            ImGui::EndPopup();
            if (isOpen) ImGui::TreePop();
            return;
        }
        ImGui::EndPopup();
    }

    if (isOpen)
    {
        for (GEntity* child : entity->Children)
        {
            RenderEntityNode(child);
        }
        ImGui::TreePop();
    }
}

void CHierarchyWindow::RenderCreateEntityPopup()
{
    if (bShowCreatePopup)
    {
        ImGui::OpenPopup("Create Entity");
        bShowCreatePopup = false;
    }

    if (ImGui::BeginPopupModal("Create Entity", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Name", NewEntityName, sizeof(NewEntityName));
        
        if (ImGui::Button("Create"))
        {
            CGameEngine::Instance().GetGame().CreateEntity(NewEntityName);
            strcpy_s(NewEntityName, sizeof(NewEntityName), "New Entity");
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            strcpy_s(NewEntityName, sizeof(NewEntityName), "New Entity");
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}
