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
    Color GetBackgroundColor() const { return backgroundColor; }

    CEntity* CreateEntity(const std::string& name);
    void DestroyEntity(CEntity* entity);
    const std::vector<CEntity*>& GetEntities() const { return Entities; }

private:
    std::vector<float> frameDuration;
    float timeAccumulator = 0.0f;
    float currentAverage = 0.0f;

    Color backgroundColor = { 0, 0, 0 };

    std::vector<CEntity*> Entities;
};
