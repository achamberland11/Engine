#pragma once
#include <vector>

class GEntity;
class CClass;

class CEntityRegistry
{
public:
    static CEntityRegistry& Instance()
    {
        static CEntityRegistry instance;
        return instance;
    }
    
    void RegisterEntity(CClass& entity)
    {
        Entities.push_back(&entity);
    }
    
    const std::vector<CClass*>& GetAllEntities() const { return Entities; }
    
private:
    std::vector<CClass*> Entities;
};
