#include "Object.h"

CClass GObject::sClass = CClass
{
    "Object",
    nullptr
};

std::vector<CProperty> GObject::sProperties;