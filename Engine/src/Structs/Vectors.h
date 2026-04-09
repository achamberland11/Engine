#pragma once
#include "SDL3/SDL_stdinc.h"

struct FColor
{
    float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
};

struct FVector2
{
    float x = 0.0f, y = 0.0f;
};

struct FVector3
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
};

struct FQuaternion
{
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;
};

struct FMatrix4x4
{
    float m[4][4];
};

struct FVector2i
{
    int x = 0, y = 0;
};

struct FVector3i
{
    int x = 0, y = 0, z = 0;
};

struct FQuaternioni
{
    float x = 0, y = 0, z = 0, w = 0;
};