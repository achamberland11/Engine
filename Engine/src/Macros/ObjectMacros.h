#pragma once
#include <cstddef>

#define GENERATE_REFLECTION() \
static CClass sClass; \
static CClass& StaticClass() { return sClass; } \
const CClass* GetClass() const override { return &sClass; }

#define REGISTER_PROPERTY(ClassName, PropertyDisplayName, PropertyValue, PropertyType) \
    ClassName::StaticClass().AddProperty(CProperty(PropertyDisplayName, PropertyType, offsetof(ClassName, PropertyValue)));

#define REGISTER_COMPONENT(CComponent) \
CComponent::StaticClass().Factory = [](CEntity* entity) \
{ \
    static ComponentFactory compFactory; \
    compFactory.NewComponent<CComponent>(entity); \
}; \
CComponentRegistry::Instance().RegisterComponent(CComponent::StaticClass());