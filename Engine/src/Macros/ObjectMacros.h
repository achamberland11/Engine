#pragma once
#include <cstddef>

#define GENERATE_REFLECTION() \
static CClass sClass; \
static CClass& StaticClass() { return sClass; } \
const CClass* GetClass() const override { return &sClass; }

#define REGISTER_PROPERTY(ClassName, PropertyDisplayName, PropertyValue, PropertyType) \
    ClassName::StaticClass().AddProperty(FProperty(PropertyDisplayName, PropertyType, offsetof(ClassName, PropertyValue)));

#define REGISTER_COMPONENT(GComponent) \
GComponent::StaticClass().Factory = [](GEntity* entity) \
{ \
    static ComponentFactory compFactory; \
    compFactory.NewComponent<GComponent>(entity); \
}; \
CComponentRegistry::Instance().RegisterComponent(GComponent::StaticClass());

#define GENERATE_COMPONENT(CanDuplicate, CanBeDisabled, CanBeDeleted) \
static constexpr bool bCanDuplicate = CanDuplicate; \
static constexpr bool bCanBeDisabled = CanBeDisabled; \
static constexpr bool bCanBeDeleted = CanBeDeleted;