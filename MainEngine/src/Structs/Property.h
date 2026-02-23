#pragma once

#include <string>

class CClass;

enum class EPropertyType
{
    Int,
    Float,
    String,
    Bool,
    Object
};

struct CProperty
{
    std::string Name;
    EPropertyType Type;
    int Offset;

    CProperty(const std::string& name, EPropertyType type, int offset)
        : Name(name), Type(type), Offset(offset) {}
};
