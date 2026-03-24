#pragma once

#include <imgui.h>
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
    bool bRendered;

    FProperty(const std::string& name, EPropertyType type, int offset, bool bRendered = true)
        : Name(name), Type(type), Offset(offset), bRendered(bRendered)
    {
    }

    void RenderProperty(void* ptr) const
    {
        if (!bRendered)
            return;

        switch (Type)
        {
        case EPropertyType::Int:
            ImGui::DragInt(Name.c_str(), static_cast<int*>(ptr), 1.0f);
            break;
        case EPropertyType::Float:
            ImGui::DragFloat(Name.c_str(), static_cast<float*>(ptr), 0.1f);
            break;
        case EPropertyType::Bool:
            ImGui::Checkbox(Name.c_str(), static_cast<bool*>(ptr));
            break;
        case EPropertyType::String:
            ImGui::InputText(Name.c_str(), static_cast<char*>(ptr), 128);
            break;
        case EPropertyType::Vector2:
            ImGui::DragFloat2(Name.c_str(), static_cast<float*>(ptr), 0.1f);
            break;
        case EPropertyType::Vector3:
            ImGui::DragFloat3(Name.c_str(), static_cast<float*>(ptr), 0.1f);
            break;
        default:
            ImGui::Text("%s: (unsupported)", Name.c_str());
            break;
        }
    }
};
