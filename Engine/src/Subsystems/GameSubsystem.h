#pragma once
#include <vector>
#include "Subsystem.h"
#include "../Game/Entity.h"
#include "../Structs/Color.h"

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

    GEntity* CreateEntity(const std::string& name);
    void DestroyEntity(GEntity* entity);
    const std::vector<GEntity*>& GetEntities() const { return Entities; }

private:
    std::vector<float> FrameDuration;
    float TimeAccumulator = 0.0f;
    float CurrentAverage = 0.0f;

    FColor BackgroundColor = { 0, 0, 0 };

    std::vector<GEntity*> Entities;
};
