#pragma once
#include <cstddef>

#define GENERATE_REFLECTION() \
static CClass sClass; \
static std::vector<CProperty> sProperties; \
static CClass& StaticClass() { return sClass; } \
const CClass* GetClass() const override { return &sClass; } \
static std::vector<CProperty>& ClassProperties() { return sProperties; } \
const std::vector<CProperty>* GetProperties() const override { return &sProperties; }

#define REGISTER_PROPERTY(ClassName, PropertyDisplayName, PropertyValue, PropertyType) \
    ClassName::ClassProperties().push_back(CProperty(#PropertyDisplayName, PropertyType, offsetof(ClassName, PropertyValue)))

#define REGISTER_COMPONENT(CComponent) 