#pragma once

#include <cstring>
#include <imgui.h>

// TODO: Window hierarchy - extend IWindow
class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void Render() = 0;

    const char* GetTitle() const { return Title; }
    bool IsVisible() const { return bVisible; }
    void SetVisible(bool visible) { bVisible = visible; }
    virtual const char* GetWindowName() const = 0;

    virtual ImGuiWindowFlags GetFlags() const
    {
        return ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoNavInputs;
    }

protected:
    const char* Title = "Window";
    bool bVisible = true;
};
