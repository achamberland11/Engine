#pragma once
#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

#include "../Structs/Vectors.h"

using json = nlohmann::json;

class CJsonWriter
{
public:
    CJsonWriter();
    ~CJsonWriter();
    
    // Basic types
    void WriteInt(const char* key, int value);
    void WriteFloat(const char* key, float value);
    void WriteBool(const char* key, bool value);
    void WriteString(const char* key, const char* value);
    
    // Vectors and structures
    void WriteVector2(const char* key, const FVector2& value);
    void WriteVector3(const char* key, const FVector3& value);
    void WriteQuaternion(const char* key, const FQuaternion& value);
    void WriteColor(const char* key, const FColor& value);
    
    // Objects and arrays
    void WriteObjectBegin(const char* key);
    void WriteObjectEnd();
    void WriteArrayBegin(const char* key);
    void WriteArrayEnd();
    
    // Write null value
    void WriteNull(const char* key);
    
    // Finalize and save
    bool SaveToFile(const std::string& filePath) const;
    std::string GetJson() const;

private:
    std::vector<json*> Stack;
    json Root;
    
    json* GetCurrent();
};

class CJsonReader
{
public:
    CJsonReader();
    ~CJsonReader();
    
    // Load from file
    bool LoadFromFile(const std::string& filePath);
    bool LoadFromString(const std::string& jsonString);
    
    // Basic types
    void ReadInt(const char* key, int& value);
    void ReadFloat(const char* key, float& value);
    void ReadBool(const char* key, bool& value);
    void ReadString(const char* key, std::string& value);
    
    // Vectors and structures
    void ReadVector2(const char* key, FVector2& value);
    void ReadVector3(const char* key, FVector3& value);
    void ReadQuaternion(const char* key, FQuaternion& value);
    void ReadColor(const char* key, FColor& value);
    
    // Objects and arrays
    void EnterObject(const char* key);
    void LeaveObject();
    void EnterArray(const char* key);
    void LeaveArray();
    bool HasKey(const char* key) const;
    int GetArraySize() const;
    bool IsArrayElement(int index);
    void MoveToArrayElement(int index);
    
private:
    std::vector<json*> Stack;
    json Root;
    std::vector<int> ArrayIndices;
    
    json* GetCurrent() const;
};
