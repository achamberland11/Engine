#pragma once

const float PI = 3.14159265358979323846f;
const float EPSILON = 1e-6f;


constexpr float DegToRad(float degrees)
{
    return degrees * (PI / 180.0f);
}

constexpr float RadToDeg(float radians)
{
    return radians * (180.0f / PI);
}
