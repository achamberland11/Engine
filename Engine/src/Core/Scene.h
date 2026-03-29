#pragma once
#include "../Game/Entity.h"
#include "../Utils/Json.h"

class CScene
{
public:
    CScene();
    ~CScene();
    
    void AddEntity(GEntity* entity);
    void RemoveEntity(GEntity* entity);
    void Clear();
    const std::vector<GEntity*>& GetEntities() const { return Entities; }
    
    // Scene serialization
    bool SaveToFile(const std::string& filePath) const;
    bool LoadFromFile(const std::string& filePath);
    
private:
    std::vector<GEntity*> Entities;
    std::string SceneName = "Scene";
    
    void SerializeEntity(CJsonWriter& writer, GEntity* entity) const;
    void DeserializeEntity(CJsonReader& reader, GEntity* entity) const;
    
};
