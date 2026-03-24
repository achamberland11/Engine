#pragma once
#include "Window.h"
#include "../Game/Entity.h"
#include "../Game/Component.h"

class CConsoleWindow : public IWindow
{
public:
    CConsoleWindow() = default;
    ~CConsoleWindow() = default;

    const char* GetWindowName() const override { return "Console##ConsoleWindow"; }

    void Render() override;
};
