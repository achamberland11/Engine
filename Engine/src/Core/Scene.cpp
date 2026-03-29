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
    for (auto entity : Entities) CGameEngine::Instance().FreeObject(entity);
    Entities.clear();
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
    CJsonReader reader;
    
    if (!reader.LoadFromFile(filePath))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load scene from file: %s", filePath.c_str());
        return false;
    }
    
    Clear();
    
    reader.EnterObject("Scene");
    {
        reader.ReadString("Name", SceneName);
        
        std::vector<std::pair<std::string, std::string>> parentLinks;
        
        reader.EnterArray("Entities");
        {
            int entityCount = reader.GetArraySize();
            for (int i = 0; i < entityCount; ++i)
            {
                reader.EnterArrayElement(i);
                {
                    GEntity* newEntity = CGameEngine::Instance().CreateEntity("TempEntity");
                    DeserializeEntity(reader, newEntity, parentLinks);
                }
                reader.LeaveObject();
            }
        }
        reader.LeaveArray();
        
        for (auto& link : parentLinks)
        {
            GEntity* child = nullptr;
            GEntity* parent = nullptr;
            
            for (GEntity* entity : Entities)
            {
                if (entity->GetName() == link.first)
                    child = entity;
                if (entity->GetName() == link.second)
                    parent = entity;
            }
            
            if (child && parent)
            {
                child->SetParent(parent);
            }
        }
    }
    reader.LeaveObject();
    
    CurrentScenePath = filePath;
    SDL_Log("Scene loaded: %s", filePath.c_str());
    return true;
}

bool CScene::Load()
{
    return false;
}

void CScene::SerializeEntity(CJsonWriter& writer, GEntity* entity) const
{
    writer.WriteObjectBegin(nullptr);
    {
        writer.WriteString("Name", entity->GetName().c_str());
        writer.WriteBool("Active", entity->IsActive());
        
        GEntity* parent = entity->GetParent();
        if (parent)
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
                        SerializeProperty(writer, component, prop, prop.Name);
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

void CScene::SerializeProperty(CJsonWriter& writer, GObject* obj, const FProperty& prop, const std::string& key) const
{
    void* ptr = (char*)obj + prop.Offset;
    
    switch (prop.Type)
    {
    case EPropertyType::Int:
        writer.WriteInt(key.c_str(), *(int*)ptr);
        break;
    case EPropertyType::Float:
        writer.WriteFloat(key.c_str(), *(float*)ptr);
        break;
    case EPropertyType::Bool:
        writer.WriteBool(key.c_str(), *(bool*)ptr);
        break;
    case EPropertyType::String:
        writer.WriteString(key.c_str(), ((std::string*)ptr)->c_str());
        break;
    case EPropertyType::Vector2:
        writer.WriteVector2(key.c_str(), *(FVector2*)ptr);
        break;
    case EPropertyType::Vector3:
        writer.WriteVector3(key.c_str(), *(FVector3*)ptr);
        break;
    case EPropertyType::Quaternion:
        writer.WriteQuaternion(key.c_str(), *(FQuaternion*)ptr);
        break;
    default:
        break;
    }
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
                            DeserializeProperty(reader, component, prop, prop.Name);
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
                GEntity* childEntity = CGameEngine::Instance().CreateEntity("TempChild");
                DeserializeEntity(reader, childEntity, parentLinks);
            }
            reader.LeaveObject();
        }
    }
    reader.LeaveArray();
}

void CScene::DeserializeProperty(CJsonReader& reader, GObject* obj, const FProperty& prop, const std::string& key) const
{
    void* ptr = (char*)obj + prop.Offset;
    
    switch (prop.Type)
    {
    case EPropertyType::Int:
    {
        int value;
        reader.ReadInt(key.c_str(), value);
        *(int*)ptr = value;
        break;
    }
    case EPropertyType::Float:
    {
        float value;
        reader.ReadFloat(key.c_str(), value);
        *(float*)ptr = value;
        break;
    }
    case EPropertyType::Bool:
    {
        bool value;
        reader.ReadBool(key.c_str(), value);
        *(bool*)ptr = value;
        break;
    }
    case EPropertyType::String:
    {
        std::string value;
        reader.ReadString(key.c_str(), value);
        *(std::string*)ptr = value;
        break;
    }
    case EPropertyType::Vector2:
    {
        FVector2 value;
        reader.ReadVector2(key.c_str(), value);
        *(FVector2*)ptr = value;
        break;
    }
    case EPropertyType::Vector3:
    {
        FVector3 value;
        reader.ReadVector3(key.c_str(), value);
        *(FVector3*)ptr = value;
        break;
    }
    case EPropertyType::Quaternion:
    {
        FQuaternion value;
        reader.ReadQuaternion(key.c_str(), value);
        *(FQuaternion*)ptr = value;
        break;
    }
    default:
        break;
    }
}
