#include "Entity.h"

CClass CEntity::sClass = CClass{
    "Entity",
   &GObject::StaticClass() 
};

std::vector<CProperty> CEntity::sProperties;

class CEntityPropertyRegistrar
{
public:
    CEntityPropertyRegistrar()
    {
        REGISTER_PROPERTY(CEntity, "Entity Name", Name, EPropertyType::String);
        REGISTER_PROPERTY(CEntity, "Active", bActive, EPropertyType::Bool);

        CEntity::StaticClass().Properties = CEntity::ClassProperties();
    }
};

static CEntityPropertyRegistrar sEntityPropertyRegistrar;

void CEntity::AddComponent(CComponent* component)
{
    Components.push_back(component);
}

void CEntity::RemoveComponent(CComponent* component)
{
    auto it = std::find(Components.begin(), Components.end(), component);
    if (it != Components.end()) Components.erase(it);
}

/*
CComponent* CEntity::GetComponent(const std::string& name)
{
}
*/
