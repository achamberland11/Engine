#pragma once

#include "../Core/Class.h"
#include "../Macros/ObjectMacros.h"

class GObject
{
public:
    virtual ~GObject() {}
    static CClass sClass;
    static std::vector<CProperty> sProperties;
    
    static CClass& StaticClass() { return sClass; }
    static std::vector<CProperty>& ClassProperties() { return sProperties; }
    
    virtual const CClass* GetClass() const = 0;
    virtual const std::vector<CProperty>* GetProperties() const = 0;

    bool IsA(const CClass& InClass) const
    {
        return GetClass()->IsChildOf(&InClass);
    }
};

template <class T>
T* Cast(GObject* InObject)
{
    if (InObject != nullptr && InObject->IsA(T::StaticClass()))
    {
        return static_cast<T*>(InObject);
    }
    return nullptr;
}
