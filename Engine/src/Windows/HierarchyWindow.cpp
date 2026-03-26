#include "HierarchyWindow.h"
#include <imgui.h>
#include "../Subsystems/EditorSubsystem.h"
#include "../Core/GameEngine.h"
#include "HierarchyWindow.h"

// TODO: Implement CHierarchyWindow - full implementation
// - Parenting support
// - Drag and drop
// - Creation/Deletion
void EHierarchyWindow::Render()
{
    if (ImGui::Begin("Hierarchy##HierarchyWindow", nullptr, GetFlags()))
    {
        if (ImGui::Button("+ Create Entity"))
        {
            bShowCreatePopup = true;
        }
        ImGui::Separator();

        const auto& entities = CGameEngine::Instance().GetEntities();
        for (GEntity* entity : entities)
        {
            if (entity->GetParent() == nullptr)
            {
                RenderEntityNode(entity);
            }
        }

        RenderCreateEntityPopup();
    }

    ImGui::End();
}

void EHierarchyWindow::RenderEntityNode(GEntity* entity)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (CGameEngine::Instance().GetEditor().GetSelectedEntity() == entity)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    if (entity->GetChildren().empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    bool isOpen = ImGui::TreeNodeEx(entity->GetName().c_str(), flags);

    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    {
        CGameEngine::Instance().GetEditor().SetSelectedEntity(entity);
    }

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Delete"))
        {
            CGameEngine::Instance().DestroyEntity(entity);
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
        for (GEntity* child : entity->GetChildren())
        {
            RenderEntityNode(child);
        }
        ImGui::TreePop();
    }
}

void EHierarchyWindow::RenderCreateEntityPopup()
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
            char baseName[64];
            strcpy_s(baseName, NewEntityName);

            auto& entities = CGameEngine::Instance().GetEntities();

            MakeUniqueName(NewEntityName, sizeof(NewEntityName), baseName, entities);

            CGameEngine::Instance().CreateEntity(NewEntityName);
            strcpy_s(NewEntityName, sizeof(NewEntityName), "Entity");
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            strcpy_s(NewEntityName, sizeof(NewEntityName), "Entity");
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

bool EHierarchyWindow::NameExists(const std::vector<GEntity*>& entities, const std::string& name)
{
    for (const GEntity* entity : entities)
    {
        if (entity->GetName() == name)
            return true;
    }
    return false;
}

void EHierarchyWindow::MakeUniqueName(char* outName, size_t outNameSize, const char* baseName,
                                      const std::vector<GEntity*>& entities)
{
    if (!NameExists(entities, baseName))
    {
        std::snprintf(outName, outNameSize, "%s", baseName);
        return;
    }

    for (int i = 0; i < 10000000; ++i)
    {
        std::snprintf(outName, outNameSize, "%s_%d", baseName, i);

        if (!NameExists(entities, outName))
            return;
    }

    std::snprintf(outName, outNameSize, "%s", "X");
}
