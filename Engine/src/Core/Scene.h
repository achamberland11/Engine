#pragma once
#include "../Game/Entity.h"

class CScene
{
public:
    CScene();
    ~CScene();
    
    void AddEntity(GEntity* entity);
    void RemoveEntity(GEntity* entity);
    void Clear();
    const std::vector<GEntity*>& GetEntities() const { return Entities; }
    
private:
    std::vector<GEntity*> Entities;
    
};
