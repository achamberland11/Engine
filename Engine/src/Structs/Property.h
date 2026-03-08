#pragma once

#include <string>

class CClass;

enum class EPropertyType
{
    Int,
    Float,
    String,
    Bool,
    Vector2,
    Vector3,
    Quaternion,
    Matrix4x4,
    Object
};

struct FProperty
{
    std::string Name;
    EPropertyType Type;
    int Offset;

    FProperty(const std::string& name, EPropertyType type, int offset)
        : Name(name), Type(type), Offset(offset) {}
};
