#pragma once
#include <vector>
#include "Subsystem.h"
#include "../Structs/Color.h"

class CGameSubsystem : public ISubsystem
{
public:
    ~CGameSubsystem() = default;

    void Start() override;
    void Shutdown() override;
    void Update(float deltaSeconds) override;

    float GetAverageFrameTime() const { return currentAverage; }
    Color GetBackgroundColor() const { return backgroundColor; }

private:
    std::vector<float> frameDuration;
    float timeAccumulator = 0.0f;
    float currentAverage = 0.0f;

    Color backgroundColor = { 0, 0, 0 };
};
