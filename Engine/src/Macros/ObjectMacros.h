#pragma once
#include <cstddef>

#define GENERATE_REFLECTION() \
static CClass sClass; \
static CClass& StaticClass() { return sClass; } \
const CClass* GetClass() const override { return &sClass; }

// Default bRendered = true
#define REGISTER_PROPERTY(ClassName, PropertyDisplayName, PropertyValue, PropertyType) \
    ClassName::StaticClass().AddProperty(FProperty(PropertyDisplayName, PropertyType, offsetof(ClassName, PropertyValue)));

// Explicit bRendered
#define REGISTER_PROPERTY_EX(ClassName, PropertyDisplayName, PropertyValue, PropertyType, bRendered) \
    ClassName::StaticClass().AddProperty(FProperty(PropertyDisplayName, PropertyType, offsetof(ClassName, PropertyValue), bRendered));


#define REGISTER_COMPONENT(GComponentClass) \
GComponentClass::StaticClass().Factory = [](GEntity* entity) \
{ \
    static CComponentFactory compFactory; \
    compFactory.NewComponent<GComponentClass>(entity); \
}; \
CComponentRegistry::Instance().RegisterComponent(GComponentClass::StaticClass());

#define REGISTER_ENTITY(GEntityClass) \
GEntityClass::StaticClass().Factory = [](GEntity* entity) \
{ \
    static CEntityFactory entityFactory; \
    entityFactory.NewEntity<GEntityClass>(); \
}; \
CEntityRegistry::Instance().RegisterEntity(GEntityClass::StaticClass());

#define GENERATE_COMPONENT(CanDuplicate, CanBeDisabled, CanBeDeleted, CanUpdateInEditor) \
static constexpr bool bCanDuplicate = CanDuplicate; \
static constexpr bool bCanBeDisabled = CanBeDisabled; \
static constexpr bool bCanBeDeleted = CanBeDeleted; \
static constexpr bool bUpdateInEditor = CanUpdateInEditor;