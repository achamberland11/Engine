#include "Counter.h"


void CCounter::Update(float deltaSeconds)
{
    if (deltaSeconds > 0.f)
        fps = 1.f / deltaSeconds;
}

float CCounter::GetFPS()
{
    return fps;
}
