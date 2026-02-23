#pragma once

class ISubsystem
{
public:
    virtual ~ISubsystem() = default;

    virtual void Start() = 0;
    virtual void Shutdown() = 0;
    virtual void Update(float deltaSeconds) = 0;
};
