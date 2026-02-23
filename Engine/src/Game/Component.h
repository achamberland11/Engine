#pragma once
#include "Object.h"

class CComponent : public GObject
{
public:
    GENERATE_REFLECTION()

    std::string Name = "Component";
    bool bEnabled = true;

    CComponent() = default;
    virtual ~CComponent() = default;
};
