#pragma once
#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

#include "../Structs/Vectors.h"

using JSON = nlohmann::json;

class CJsonWriter
{
public:
    CJsonWriter();
    ~CJsonWriter();
    
    // Basic types
    void WriteInt(const char* key, int value) const;
    void WriteFloat(const char* key, float value) const;
    void WriteBool(const char* key, bool value) const;
    void WriteString(const char* key, const char* value) const;
    
    // Vectors and structures
    void WriteVector2(const char* key, const FVector2& value) const;
    void WriteVector3(const char* key, const FVector3& value) const;
    void WriteQuaternion(const char* key, const FQuaternion& value) const;
    void WriteColor(const char* key, const FColor& value) const;
    
    // Objects and arrays
    void WriteObjectBegin(const char* key);
    void WriteObjectEnd();
    void WriteArrayBegin(const char* key);
    void WriteArrayEnd();
    
    // Write null value
    void WriteNull(const char* key) const;
    
    // Finalize and save
    bool SaveToFile(const std::string& filePath) const;
    std::string GetJson() const;

private:
    std::vector<JSON*> Stack;
    JSON Root;
    
    JSON* GetCurrent() const;
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
    void ReadInt(const char* key, int& value) const;
    void ReadFloat(const char* key, float& value) const;
    void ReadBool(const char* key, bool& value) const;
    void ReadString(const char* key, std::string& value) const;
    
    // Vectors and structures
    void ReadVector2(const char* key, FVector2& value) const;
    void ReadVector3(const char* key, FVector3& value) const;
    void ReadQuaternion(const char* key, FQuaternion& value) const;
    void ReadColor(const char* key, FColor& value) const;
    
    // Objects and arrays
    void EnterObject(const char* key);
    void LeaveObject();
    void EnterArray(const char* key);
    void LeaveArray();
    void EnterArrayElement(int index);
    bool HasKey(const char* key) const;
    bool IsValueNull(const char* key) const;
    int GetArraySize() const;
    bool IsArrayElement(int index) const;
    void MoveToArrayElement(int index);
    
private:
    std::vector<JSON*> Stack;
    JSON Root;
    std::vector<int> ArrayIndices;
    
    JSON* GetCurrent() const;
};
