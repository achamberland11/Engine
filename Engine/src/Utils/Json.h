#pragma once
#include <string>

#include "../Structs/Vectors.h"

class CJsonWriter
{
public:
    void WriteInt(const char* key, int value);
    void WriteFloat(const char* key, float value);
    void WriteBool(const char* key, bool value);
    void WriteString(const char* key, const char* value);
    void WriteVector3(const char* key, const FVector3& value);
    void WriteObjectBegin(const char* key);
    void WriteObjectEnd();
    
};

class CJsonReader
{
public:
    void ReadInt(const char* key, int& value);
    void ReadFloat(const char* key, float& value);
    void ReadBool(const char* key, bool& value);
    void ReadString(const char* key, std::string& value);
    void ReadVector3(const char* key, FVector3& value);
    void EnterObject(const char* key);
    void LeaveObject();
    void EnterArray(const char* key);
    void LeaveArray();
};