#include "Scene.h"

#include "GameEngine.h"

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
    for (auto entity : Entities) CGameEngine::Instance().DestroyEntity(entity);
    Entities.clear();
}

bool CScene::SaveToFile(const std::string& filePath) const
{
    CJsonWriter writer;

    writer.WriteObjectBegin("Scene");
    {
        writer.WriteString("Name", SceneName.c_str());
        writer.WriteArrayBegin("Entities");
        {
            for (GEntity* entity : Entities)
            {
                SerializeEntity(writer, entity);
            }
        }
        writer.WriteArrayEnd();
    }
    writer.WriteObjectEnd();

    return writer.SaveToFile(filePath);
}

bool CScene::LoadFromFile(const std::string& filePath)
{
    CJsonReader reader;
    
    if (!reader.LoadFromFile(filePath)) return false;
    
    Clear();
    
    reader.EnterObject("Scene");
    {
        reader.ReadString("Name", SceneName);
        
        reader.EnterArray("Entities");
        {
            int entityCount = reader.GetArraySize();
            for (int i = 0; i < entityCount; ++i)
            {
                if (reader.IsArrayElement(i))
                {
                    GEntity* newEntity = CGameEngine::Instance().CreateEntity("NewEntity");
                    DeserializeEntity(reader, newEntity);
                    AddEntity(newEntity);
                }
            }
        }
        reader.LeaveArray();
    }
    reader.LeaveObject();
    
    return true;
}

void CScene::SerializeEntity(CJsonWriter& writer, GEntity* entity) const
{
    writer.WriteObjectBegin(nullptr);
    {
        // TODO: add ID system
        // writer.WriteString("ID", entity->GetName().c_str());
        writer.WriteString("Name", entity->GetName().c_str());
        
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
                }
                writer.WriteObjectEnd();
            }
        }
        writer.WriteArrayEnd();
    }
    writer.WriteObjectEnd();
}

void CScene::DeserializeEntity(CJsonReader& reader, GEntity* entity) const
{
    reader.EnterObject(nullptr);
    {
        std::string entityName;
        reader.ReadString("Name", entityName);
        entity->SetName(entityName);
        
        reader.EnterArray("Components");
        {
            int componentCount = reader.GetArraySize();
            for (int i = 0; i < componentCount; ++i)
            {
                if (reader.IsArrayElement(i))
                {
                    reader.EnterObject(nullptr);
                    {
                        std::string componentType;
                        reader.ReadString("Type", componentType);
                    }
                    reader.LeaveObject();
                }
            }
        }
        reader.LeaveArray();
    }
    reader.LeaveObject();
}
