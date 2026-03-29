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
    
    std::string GetSceneName() const { return SceneName; }
    void SetSceneName(const std::string& name) { SceneName = name; }
    
    std::string GetCurrentScenePath() const { return CurrentScenePath; }
    void SetCurrentScenePath(const std::string& path) { CurrentScenePath = path; }
    
    bool SaveToFile(const std::string& filePath);
    bool Save();
    bool LoadFromFile(const std::string& filePath);
    bool Load();
    bool IsSaved() const { return !CurrentScenePath.empty(); }
    
private:
    void SerializeEntity(CJsonWriter& writer, GEntity* entity) const;
    void DeserializeEntity(CJsonReader& reader, GEntity* entity, std::vector<std::pair<std::string, std::string>>& parentLinks);
    
    std::vector<GEntity*> Entities;
    std::string SceneName = "Scene";
    std::string CurrentScenePath;
    
    void SerializeProperty(CJsonWriter& writer, GObject* obj, const FProperty& prop, const std::string& key) const;
    void DeserializeProperty(CJsonReader& reader, GObject* obj, const FProperty& prop, const std::string& key) const;
    
};
