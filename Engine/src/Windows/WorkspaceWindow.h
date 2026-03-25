#pragma once
#include "Window.h"

class EWorkspaceWindow : public IWindow
{
public:
    EWorkspaceWindow() = default;
    ~EWorkspaceWindow() = default;

    const char* GetWindowName() const override { return "Workspace##WorkspaceWindow"; }


    void Render() override;

private:
    bool bIsInitialized = false;
};
