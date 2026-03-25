#include "EditorSubsystem.h"

void CEditorSubsystem::Start()
{
    WindowManager = new CWindowManager();
    WindowManager->RegisterWindow<EWorkspaceWindow>();
    WindowManager->RegisterWindow<EDebugWindow>();
    WindowManager->RegisterWindow<EConsoleWindow>();
    WindowManager->RegisterWindow<EInspectorWindow>();
    WindowManager->RegisterWindow<EHierarchyWindow>();
}

void CEditorSubsystem::Shutdown()
{
    delete WindowManager;
}

void CEditorSubsystem::Update(float deltaSeconds)
{
}

void CEditorSubsystem::Render() const
{
    WindowManager->RenderWindows();
}