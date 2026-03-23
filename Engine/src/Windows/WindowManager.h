#pragma once
#include <vector>

#include "Window.h"
#include <memory>
#include <string>

// TODO: 2. WindowManager - manages windows, docking, serialization
class CWindowManager
{
public:
    CWindowManager() = default;
    ~CWindowManager() = default;
    
    // TODO: 3. Window hierarchy - extend IWindow (integrate new methods)
    void RenderWindows();
    
    // TODO: 8. Layout persistence - using ImGui native methods
    void SaveLayout();
    void LoadLayout();
    
    template<typename T>
    void RegisterWindow();
    
    template<typename T>
    T* GetWindow();
    
private:
    std::vector<std::unique_ptr<IWindow>> Windows;
    std::string LayoutPath = "imgui.ini";
};

template <typename T>
void CWindowManager::RegisterWindow()
{
    static_assert(std::is_base_of<IWindow, T>::value, "T must be a subclass of IWindow");
    // static_assert(std::is_default_constructible<T>::value, "T must be default constructible");
    auto window = std::make_unique<T>();
    Windows.push_back(std::move(window));
}

template <typename T>
T* CWindowManager::GetWindow()
{
    for (auto& window : Windows)
    {
        if (T* casted = dynamic_cast<T*>(window.get()))
        {
            return casted;
        }
    }
    return nullptr;
}