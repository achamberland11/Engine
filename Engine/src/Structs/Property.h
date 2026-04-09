#pragma once

#include <imgui.h>
#include <string>

#include "Colliders.h"
#include "../Utils/Json.h"

class GObject;
class CClass;

enum class EPropertyType
{
    Int,
    Float,
    String,
    Bool,
    Color,
    Vector2,
    Vector3,
    Quaternion,
    Matrix4x4,
    Object,
    ColliderType2D,
    ColliderType3D,
};

static const char* sColliderTypeNames[] = {"Box", "Sphere", "Capsule", "Mesh"};
static const char* sColliderType2DNames[] = {"Rectangle", "Circle"};

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
        case EPropertyType::String:
            ImGui::InputText(Name.c_str(), static_cast<char*>(ptr), 128);
            break;
        case EPropertyType::Bool:
            ImGui::Checkbox(Name.c_str(), static_cast<bool*>(ptr));
            break;
        case EPropertyType::Color:
            ImGui::ColorEdit4(Name.c_str(), static_cast<float*>(ptr));
            break;
        case EPropertyType::Vector2:
            ImGui::DragFloat2(Name.c_str(), static_cast<float*>(ptr), 0.1f);
            break;
        case EPropertyType::Vector3:
            ImGui::DragFloat3(Name.c_str(), static_cast<float*>(ptr), 0.1f);
            break;
        case EPropertyType::Quaternion:
            ImGui::DragFloat4(Name.c_str(), static_cast<float*>(ptr), 0.1f);
            break;
        case EPropertyType::ColliderType2D:
            ImGui::Combo("Collider Type", static_cast<int*>(ptr), sColliderType2DNames, IM_ARRAYSIZE(sColliderType2DNames));
            break;
        case EPropertyType::ColliderType3D:
            ImGui::Combo("Collider Type", static_cast<int*>(ptr), sColliderTypeNames, IM_ARRAYSIZE(sColliderTypeNames));
            break;
        default:
            ImGui::Text("%s: (unsupported)", Name.c_str());
            break;
        }
    }

    void SerializeProperty(CJsonWriter& writer, GObject* obj) const
    {
        void* ptr = (char*)obj + Offset;

        switch (Type)
        {
        case EPropertyType::Int:
            writer.WriteInt(Name.c_str(), *(int*)ptr);
            break;
        case EPropertyType::Float:
            writer.WriteFloat(Name.c_str(), *(float*)ptr);
            break;
        case EPropertyType::String:
            writer.WriteString(Name.c_str(), ((std::string*)ptr)->c_str());
            break;
        case EPropertyType::Bool:
            writer.WriteBool(Name.c_str(), *(bool*)ptr);
            break;
        case EPropertyType::Color:
            writer.WriteColor(Name.c_str(), *(FColor*)ptr);
            break;
        case EPropertyType::Vector2:
            writer.WriteVector2(Name.c_str(), *(FVector2*)ptr);
            break;
        case EPropertyType::Vector3:
            writer.WriteVector3(Name.c_str(), *(FVector3*)ptr);
            break;
        case EPropertyType::Quaternion:
            writer.WriteQuaternion(Name.c_str(), *(FQuaternion*)ptr);
            break;
        case EPropertyType::ColliderType2D:
            writer.WriteInt(Name.c_str(), static_cast<int>(*(EColliderType2D*)ptr));
            break;
        case EPropertyType::ColliderType3D:
            writer.WriteInt(Name.c_str(), static_cast<int>(*(EColliderType3D*)ptr));
            break;
        default:
            break;
        }
    }

    void DeserializeProperty(CJsonReader& reader, GObject* obj) const
    {
        void* ptr = (char*)obj + Offset;

        switch (Type)
        {
        case EPropertyType::Int:
            {
                int value;
                reader.ReadInt(Name.c_str(), value);
                *(int*)ptr = value;
                break;
            }
        case EPropertyType::Float:
            {
                float value;
                reader.ReadFloat(Name.c_str(), value);
                *(float*)ptr = value;
                break;
            }
        case EPropertyType::Bool:
            {
                bool value;
                reader.ReadBool(Name.c_str(), value);
                *(bool*)ptr = value;
                break;
            }
        case EPropertyType::String:
            {
                std::string value;
                reader.ReadString(Name.c_str(), value);
                *(std::string*)ptr = value;
                break;
            }
        case EPropertyType::Color:
            {
                FColor value;
                reader.ReadColor(Name.c_str(), value);
                *(FColor*)ptr = value;
                break;
            }
        case EPropertyType::Vector2:
            {
                FVector2 value;
                reader.ReadVector2(Name.c_str(), value);
                *(FVector2*)ptr = value;
                break;
            }
        case EPropertyType::Vector3:
            {
                FVector3 value;
                reader.ReadVector3(Name.c_str(), value);
                *(FVector3*)ptr = value;
                break;
            }
        case EPropertyType::Quaternion:
            {
                FQuaternion value;
                reader.ReadQuaternion(Name.c_str(), value);
                *(FQuaternion*)ptr = value;
                break;
            }
        case EPropertyType::ColliderType2D:
            {
                int value;
                reader.ReadInt(Name.c_str(), value);
                *(EColliderType2D*)ptr = (EColliderType2D)value;
            }
        case EPropertyType::ColliderType3D:
            {
                int value;
                reader.ReadInt(Name.c_str(), value);
                *(EColliderType3D*)ptr = (EColliderType3D)value;
            }
        default:
            break;
        }
    }
};
