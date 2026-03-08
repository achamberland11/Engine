#pragma once
#include <vector>

class GComponent;
class GEntity;

class CComponentRegistry
{
public:
    static CComponentRegistry& Instance()
    {
        static CComponentRegistry instance;
        return instance;   
    }
    
    void RegisterComponent(CClass& component)
    {
        Components.push_back(&component);
    }
    
    const std::vector<CClass*>& GetAllComponents() const { return Components; }
    
private:
    std::vector<CClass*> Components;
};