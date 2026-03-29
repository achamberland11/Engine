#pragma once
#include "Window.h"
#include <string>

class EToolbarWindow : public IWindow
{
public:
    EToolbarWindow() = default;
    ~EToolbarWindow() = default;

    const char* GetWindowName() const override { return "Toolbar##ToolbarWindow"; }

    void Render() override;

    void NewScene();
    void SaveScene();
    void OpenScene();

    static std::string GetLastSaveDirectory() { return LastSaveDirectory; }
    static void SetLastSaveDirectory(const std::string& dir) { LastSaveDirectory = dir; }

private:
    void RenderSceneInfo();

    static std::string LastSaveDirectory;
};
