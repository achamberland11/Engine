#pragma once

#include "../Core/Class.h"
#include "../Macros/ObjectMacros.h"

class GObject
{
public:
    virtual ~GObject() {}
    static CClass sClass;
    
    static CClass& StaticClass() { return sClass; }
    virtual const CClass* GetClass() const = 0;

    bool IsA(const CClass& InClass) const
    {
        return GetClass()->IsChildOf(&InClass);
    }
    
    //virtual void Start() = 0;
    //virtual void Update(float deltaSeconds) = 0;
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
