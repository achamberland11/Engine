#pragma once
#include "Object.h"

class CComponent : GObject
{
public:
    GENERATE_REFLECTION()

    std::string Name = "Entity";
    bool bEnabled = true;

    CComponent() = default;
    virtual ~CComponent() = default;
};
