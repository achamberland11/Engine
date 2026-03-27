#include "HierarchyWindow.h"
#include <imgui.h>
#include "../Subsystems/EditorSubsystem.h"
#include "../Core/GameEngine.h"
#include "HierarchyWindow.h"

#include "../Game/Entities/EntityRegistry.h"

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
            bShowSelectEntityPopup = true;
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

        RenderSelectEntityPopup();
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

void EHierarchyWindow::RenderSelectEntityPopup()
{
    if (bShowSelectEntityPopup)
    {
        ImGui::OpenPopup("Select Entity Type");
        bShowSelectEntityPopup = false;
        EntitySearchBuffer[0] = '\0';
        SelectedEntityType = nullptr;
    }

    if (ImGui::BeginPopupModal("Select Entity Type", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Search##EntitySearch", EntitySearchBuffer, sizeof(EntitySearchBuffer));
        ImGui::Separator();

        const auto& entityTypes = CEntityRegistry::Instance().GetAllEntities();
        for (CClass* entityClass : entityTypes)
        {
            if (EntitySearchBuffer[0] != '\0' &&
                !FuzzyMatch(EntitySearchBuffer, entityClass->DisplayName.c_str()))
            {
                continue;
            }

            if (ImGui::Selectable(entityClass->DisplayName.c_str()))
            {
                SelectedEntityType = entityClass;
                bShowCreatePopup = true;
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::Separator();
        if (ImGui::Button("Cancel##SelectEntity"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}


void EHierarchyWindow::RenderCreateEntityPopup()
{
    if (bShowCreatePopup && SelectedEntityType)
    {
        ImGui::OpenPopup("Create Entity");
        bShowCreatePopup = false;
        strcpy_s(NewEntityName, sizeof(NewEntityName), SelectedEntityType->DisplayName.c_str());
    }

    if (ImGui::BeginPopupModal("Create Entity", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Name##EntityName", NewEntityName, sizeof(NewEntityName));

        if (ImGui::Button("Create"))
        {
            char baseName[64];
            strcpy_s(baseName, NewEntityName);

            auto& entities = CGameEngine::Instance().GetEntities();

            MakeUniqueName(NewEntityName, sizeof(NewEntityName), baseName, entities);

            if (SelectedEntityType->Factory)
            {
                SelectedEntityType->Factory(nullptr, NewEntityName);
            }
            
            strcpy_s(NewEntityName, sizeof(NewEntityName), "Entity");
            SelectedEntityType = nullptr;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel##CreateEntity"))
        {
            strcpy_s(NewEntityName, sizeof(NewEntityName), "Entity");
            SelectedEntityType = nullptr;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

// TODO: Make this function global to the project
bool EHierarchyWindow::NameExists(const std::vector<GEntity*>& entities, const std::string& name)
{
    for (const GEntity* entity : entities)
    {
        if (entity->GetName() == name)
            return true;
    }
    return false;
}

// TODO: Make this function global to the project
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

// TODO: Make this function global to the project (and remove the other one)
bool EHierarchyWindow::FuzzyMatch(const char* pattern, const char* text)
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
