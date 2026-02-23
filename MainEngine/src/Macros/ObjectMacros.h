#pragma once

#define GENERATE_REFLECTION() \
static CClass sClass; \
static CClass& StaticClass() { return sClass; } \
CClass* GetClass() const override { return &sClass; }