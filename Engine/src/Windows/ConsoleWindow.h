#pragma once
#include "../Windows/Window.h"

class EConsoleWindow : public IWindow
{
public:
    EConsoleWindow() { Title = "Console"; }

    const char* GetWindowName() const override { return "Console##ConsoleWindow"; }

    void Render() override;
};
