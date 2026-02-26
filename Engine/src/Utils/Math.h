#pragma once

const float PI = 3.14159265358979323846f;
const float EPSILON = 1e-6f;

struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;
};

struct Vector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Quaternion
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 1.0f;
};

struct Matrix4x4
{
    float m[4][4];
};

constexpr float DegToRad(float degrees)
{
    return degrees * (PI / 180.0f);
}

constexpr float RadToDeg(float radians)
{
    return radians * (180.0f / PI);
}
