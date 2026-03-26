#pragma once
#include <vector>

#include "EditorSubsystem.h"
#include "Subsystem.h"
#include "../Game/Entity.h"
#include "../Structs/Vectors.h"

class CGameSubsystem : public ISubsystem
{
public:
    CGameSubsystem() = default;
    ~CGameSubsystem() = default;

    void Start() override;
    void Shutdown() override;
    void Update(float deltaSeconds) override;

    float GetAverageFrameTime() const { return CurrentAverage; }
    FColor GetBackgroundColor() const { return BackgroundColor; }


private:
    std::vector<float> FrameDuration;
    float TimeAccumulator = 0.0f;
    float CurrentAverage = 0.0f;

    FColor BackgroundColor = { 0, 0, 0 };

    std::vector<GEntity*> Entities;
    EEditorMode* EditorMode = nullptr;
};
