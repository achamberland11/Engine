#include "Json.h"
#include <fstream>
#include <iostream>

// ============= CJsonWriter =============

CJsonWriter::CJsonWriter()
{
    Root = json::object();
    Stack.push_back(&Root);
}

CJsonWriter::~CJsonWriter() = default;

json* CJsonWriter::GetCurrent()
{
    if (Stack.empty())
        return nullptr;
    return Stack.back();
}

void CJsonWriter::WriteInt(const char* key, int value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = value;
    }
}

void CJsonWriter::WriteFloat(const char* key, float value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = value;
    }
}

void CJsonWriter::WriteBool(const char* key, bool value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = value;
    }
}

void CJsonWriter::WriteString(const char* key, const char* value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = value;
    }
}

void CJsonWriter::WriteVector2(const char* key, const FVector2& value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = json::object();
        (*current)[key]["X"] = value.x;
        (*current)[key]["Y"] = value.y;
    }
}

void CJsonWriter::WriteVector3(const char* key, const FVector3& value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = json::object();
        (*current)[key]["X"] = value.x;
        (*current)[key]["Y"] = value.y;
        (*current)[key]["Z"] = value.z;
    }
}

void CJsonWriter::WriteQuaternion(const char* key, const FQuaternion& value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = json::object();
        (*current)[key]["X"] = value.x;
        (*current)[key]["Y"] = value.y;
        (*current)[key]["Z"] = value.z;
        (*current)[key]["W"] = value.w;
    }
}

void CJsonWriter::WriteColor(const char* key, const FColor& value)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = json::object();
        (*current)[key]["R"] = static_cast<int>(value.r * 255.0f);
        (*current)[key]["G"] = static_cast<int>(value.g * 255.0f);
        (*current)[key]["B"] = static_cast<int>(value.b * 255.0f);
        (*current)[key]["A"] = 255;
    }
}

void CJsonWriter::WriteNull(const char* key)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = nullptr;
    }
}

void CJsonWriter::WriteObjectBegin(const char* key)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = json::object();
        Stack.push_back(&(*current)[key]);
    }
}

void CJsonWriter::WriteObjectEnd()
{
    if (Stack.size() > 1)
    {
        Stack.pop_back();
    }
}

void CJsonWriter::WriteArrayBegin(const char* key)
{
    if (auto* current = GetCurrent())
    {
        (*current)[key] = json::array();
        Stack.push_back(&(*current)[key]);
    }
}

void CJsonWriter::WriteArrayEnd()
{
    if (Stack.size() > 1)
    {
        Stack.pop_back();
    }
}

bool CJsonWriter::SaveToFile(const std::string& filePath) const
{
    try
    {
        std::ofstream file(filePath);
        if (!file.is_open())
            return false;
        
        file << Root.dump(2); // Pretty print with 2-space indent
        file.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error saving JSON to file: " << e.what() << std::endl;
        return false;
    }
}

std::string CJsonWriter::GetJson() const
{
    return Root.dump(2);
}

// ============= CJsonReader =============

CJsonReader::CJsonReader() = default;

CJsonReader::~CJsonReader() = default;

json* CJsonReader::GetCurrent() const
{
    if (Stack.empty())
        return nullptr;
    return Stack.back();
}

bool CJsonReader::LoadFromFile(const std::string& filePath)
{
    try
    {
        std::ifstream file(filePath);
        if (!file.is_open())
            return false;
        
        file >> Root;
        Stack.clear();
        Stack.push_back(&Root);
        ArrayIndices.clear();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading JSON from file: " << e.what() << std::endl;
        return false;
    }
}

bool CJsonReader::LoadFromString(const std::string& jsonString)
{
    try
    {
        Root = json::parse(jsonString);
        Stack.clear();
        Stack.push_back(&Root);
        ArrayIndices.clear();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error parsing JSON string: " << e.what() << std::endl;
        return false;
    }
}

void CJsonReader::ReadInt(const char* key, int& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_number_integer())
        {
            value = current->at(key).get<int>();
        }
    }
}

void CJsonReader::ReadFloat(const char* key, float& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_number())
        {
            value = current->at(key).get<float>();
        }
    }
}

void CJsonReader::ReadBool(const char* key, bool& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_boolean())
        {
            value = current->at(key).get<bool>();
        }
    }
}

void CJsonReader::ReadString(const char* key, std::string& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_string())
        {
            value = current->at(key).get<std::string>();
        }
    }
}

void CJsonReader::ReadVector2(const char* key, FVector2& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_object())
        {
            const auto& obj = current->at(key);
            if (obj.contains("X")) value.x = obj.at("X").get<float>();
            if (obj.contains("Y")) value.y = obj.at("Y").get<float>();
        }
    }
}

void CJsonReader::ReadVector3(const char* key, FVector3& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_object())
        {
            const auto& obj = current->at(key);
            if (obj.contains("X")) value.x = obj.at("X").get<float>();
            if (obj.contains("Y")) value.y = obj.at("Y").get<float>();
            if (obj.contains("Z")) value.z = obj.at("Z").get<float>();
        }
    }
}

void CJsonReader::ReadQuaternion(const char* key, FQuaternion& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_object())
        {
            const auto& obj = current->at(key);
            if (obj.contains("X")) value.x = obj.at("X").get<float>();
            if (obj.contains("Y")) value.y = obj.at("Y").get<float>();
            if (obj.contains("Z")) value.z = obj.at("Z").get<float>();
            if (obj.contains("W")) value.w = obj.at("W").get<float>();
        }
    }
}

void CJsonReader::ReadColor(const char* key, FColor& value)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_object())
        {
            const auto& obj = current->at(key);
            if (obj.contains("R")) value.r = obj.at("R").get<int>() / 255.0f;
            if (obj.contains("G")) value.g = obj.at("G").get<int>() / 255.0f;
            if (obj.contains("B")) value.b = obj.at("B").get<int>() / 255.0f;
        }
    }
}

void CJsonReader::EnterObject(const char* key)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_object())
        {
            Stack.push_back(&(*current)[key]);
        }
    }
}

void CJsonReader::LeaveObject()
{
    if (Stack.size() > 1)
    {
        Stack.pop_back();
    }
}

void CJsonReader::EnterArray(const char* key)
{
    if (auto* current = GetCurrent())
    {
        if (current->contains(key) && current->at(key).is_array())
        {
            Stack.push_back(&(*current)[key]);
            ArrayIndices.push_back(0);
        }
    }
}

void CJsonReader::LeaveArray()
{
    if (Stack.size() > 1)
    {
        Stack.pop_back();
        ArrayIndices.pop_back();
    }
}

bool CJsonReader::HasKey(const char* key) const
{
    if (auto* current = GetCurrent())
    {
        return current->contains(key);
    }
    return false;
}

int CJsonReader::GetArraySize() const
{
    if (auto* current = GetCurrent())
    {
        if (current->is_array())
        {
            return current->size();
        }
    }
    return 0;
}

bool CJsonReader::IsArrayElement(int index)
{
    if (auto* current = GetCurrent())
    {
        if (current->is_array() && index >= 0 && index < static_cast<int>(current->size()))
        {
            return true;
        }
    }
    return false;
}

void CJsonReader::MoveToArrayElement(int index)
{
    if (!ArrayIndices.empty() && IsArrayElement(index))
    {
        ArrayIndices.back() = index;
    }
}