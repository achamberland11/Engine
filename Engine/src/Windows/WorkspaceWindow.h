#pragma once
#include "Window.h"

class CWorkspaceWindow : public IWindow
{
public:
    CWorkspaceWindow() = default;
    ~CWorkspaceWindow() = default;

    const char* GetWindowName() const override { return "Workspace##WorkspaceWindow"; }


    void Render() override;

private:
    bool bIsInitialized = false;
};
