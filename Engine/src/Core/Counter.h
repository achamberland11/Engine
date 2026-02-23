#pragma once

class CCounter
{
public:
    void Update(float deltaSeconds);
    float GetFPS();

private:
    float fps = 0.f;
};
