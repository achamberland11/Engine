#pragma once
#include "../Windows/Window.h"

class CConsoleWindow : public IWindow
{
public:
    CConsoleWindow() { Title = "Console"; }

    const char* GetWindowName() const override { return "Console##ConsoleWindow"; }

    void Render() override;
};
