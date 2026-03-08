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

    float GetAverageFrameTime() const { return currentAverage; }
    FColor GetBackgroundColor() const { return backgroundColor; }

    GEntity* CreateEntity(const std::string& name);
    void DestroyEntity(GEntity* entity);
    const std::vector<GEntity*>& GetEntities() const { return Entities; }

private:
    std::vector<float> frameDuration;
    float timeAccumulator = 0.0f;
    float currentAverage = 0.0f;

    FColor backgroundColor = { 0, 0, 0 };

    std::vector<GEntity*> Entities;
};
