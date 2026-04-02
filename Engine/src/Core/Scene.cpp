#include "Scene.h"

#include "GameEngine.h"
#include "../Game/Components/ComponentRegistry.h"
#include "../Game/Entities/EntityRegistry.h"
#include "SDL3/SDL_log.h"

CScene::CScene()
{
}

CScene::~CScene()
{
    Clear();
}

void CScene::AddEntity(GEntity* entity)
{
    Entities.push_back(entity);
}

void CScene::RemoveEntity(GEntity* entity)
{
    auto it = std::find(Entities.begin(), Entities.end(), entity);
    if (it != Entities.end()) Entities.erase(it);
}

void CScene::Clear()
{
    for (GEntity* entity : Entities)
    {
        entity->SetParent(nullptr);
    }
    for (auto entity : Entities)
    {
        CGameEngine::Instance().FreeObject(entity);
    }
    Entities.clear();
}

GEntity* CScene::FindEntity(const std::string& name) const
{
    for (GEntity* entity : Entities)
    {
        if (entity->GetName() == name)
            return entity;
    }
    return nullptr;
}

bool CScene::SaveToFile(const std::string& filePath)
{
    CJsonWriter writer;

    writer.WriteObjectBegin("Scene");
    {
        writer.WriteString("Name", SceneName.c_str());
        writer.WriteArrayBegin("Entities");
        {
            for (GEntity* entity : Entities)
            {
                if (entity->GetParent() == nullptr)
                {
                    SerializeEntity(writer, entity);
                }
            }
        }
        writer.WriteArrayEnd();
    }
    writer.WriteObjectEnd();

    bool success = writer.SaveToFile(filePath);
    if (success)
    {
        CurrentScenePath = filePath;
    }
    return success;
}

bool CScene::Save()
{
    if (CurrentScenePath.empty())
    {
        return false;
    }
    return SaveToFile(CurrentScenePath);
}

bool CScene::LoadFromFile(const std::string& filePath)
{
    bIsLoadingScene = true;
    
    CJsonReader reader;
    
    if (!reader.LoadFromFile(filePath))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load scene from file: %s", filePath.c_str());
        bIsLoadingScene = false;
        return false;
    }
    
    std::string loadedSceneName = "Scene";
    std::vector<std::pair<std::string, std::string>> parentLinks;
    std::vector<GEntity*> tempEntities;
    
    reader.EnterObject("Scene");
    {
        reader.ReadString("Name", loadedSceneName);
        
        reader.EnterArray("Entities");
        {
            int entityCount = reader.GetArraySize();
            for (int i = 0; i < entityCount; ++i)
            {
                reader.EnterArrayElement(i);
                {
                    GEntity* newEntity = CGameEngine::Instance().NewObject<GEntity>();
                    DeserializeEntity(reader, newEntity, parentLinks);
                    tempEntities.push_back(newEntity);
                }
                reader.LeaveObject();
            }
        }
        reader.LeaveArray();
    }
    reader.LeaveObject();
    
    Clear();
    
    SceneName = loadedSceneName;
    
    for (GEntity* entity : tempEntities)
    {
        Entities.push_back(entity);
    }
    tempEntities.clear();
    
    for (auto& link : parentLinks)
    {
        GEntity* child = FindEntity(link.first);
        GEntity* parent = FindEntity(link.second);
        if (child && parent)
        {
            child->SetParent(parent);
        }
    }
    
    CurrentScenePath = filePath;
    SDL_Log("Scene loaded: %s", filePath.c_str());
    bIsLoadingScene = false;
    return true;
}

bool CScene::Load()
{
    return false;
}

void CScene::SerializeEntity(CJsonWriter& writer, const GEntity* entity) const
{
    writer.WriteObjectBegin(nullptr);
    {
        writer.WriteString("Name", entity->GetName().c_str());
        writer.WriteBool("Active", entity->IsActive());

        if (const GEntity* parent = entity->GetParent())
            writer.WriteString("Parent", parent->GetName().c_str());
        else
            writer.WriteNull("Parent");
        
        writer.WriteArrayBegin("Components");
        {
            for (GComponent* component : entity->GetComponents())
            {
                writer.WriteObjectBegin(nullptr);
                {
                    writer.WriteString("Type", component->GetClass()->GetName().c_str());
                    
                    for (const FProperty& prop : component->GetClass()->Properties)
                    {
                        prop.SerializeProperty(writer, component);
                    }
                }
                writer.WriteObjectEnd();
            }
        }
        writer.WriteArrayEnd();
        
        writer.WriteArrayBegin("Children");
        {
            for (GEntity* child : entity->GetChildren())
            {
                SerializeEntity(writer, child);
            }
        }
        writer.WriteArrayEnd();
    }
    writer.WriteObjectEnd();
}

void CScene::DeserializeEntity(CJsonReader& reader, GEntity* entity, std::vector<std::pair<std::string, std::string>>& parentLinks)
{
    std::string entityName;
    reader.ReadString("Name", entityName);
    entity->SetName(entityName);
    
    bool isActive = true;
    if (reader.HasKey("Active"))
    {
        reader.ReadBool("Active", isActive);
        entity->SetActive(isActive);
    }
    
    std::string parentName;
    if (reader.HasKey("Parent") && !reader.IsValueNull("Parent"))
    {
        reader.ReadString("Parent", parentName);
        parentLinks.push_back({entityName, parentName});
    }
    
    reader.EnterArray("Components");
    {
        int componentCount = reader.GetArraySize();
        for (int i = 0; i < componentCount; ++i)
        {
            reader.EnterArrayElement(i);
            {
                std::string componentType;
                reader.ReadString("Type", componentType);
                
                GComponent* component = nullptr;
                for (CClass* compClass : CComponentRegistry::Instance().GetAllComponents())
                {
                    if (compClass->GetName() == componentType)
                    {
                        compClass->Factory(entity, "");
                        auto& components = entity->GetComponents();
                        if (!components.empty())
                        {
                            component = components.back();
                        }
                        break;
                    }
                }
                
                if (component)
                {
                    for (const FProperty& prop : component->GetClass()->Properties)
                    {
                        if (reader.HasKey(prop.Name.c_str()))
                        {
                            prop.DeserializeProperty(reader, component);
                        }
                    }
                }
            }
            reader.LeaveObject();
        }
    }
    reader.LeaveArray();
    
    reader.EnterArray("Children");
    {
        int childCount = reader.GetArraySize();
        for (int i = 0; i < childCount; ++i)
        {
            reader.EnterArrayElement(i);
            {
                GEntity* childEntity = CGameEngine::Instance().NewObject<GEntity>();
                DeserializeEntity(reader, childEntity, parentLinks);
                entity->AddChild(childEntity);
            }
            reader.LeaveObject();
        }
    }
    reader.LeaveArray();
}