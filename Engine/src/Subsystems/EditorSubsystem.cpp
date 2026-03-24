#include "EditorSubsystem.h"

void CEditorSubsystem::Start()
{
    WindowManager = new CWindowManager();
    WindowManager->RegisterWindow<CWorkspaceWindow>();
    WindowManager->RegisterWindow<CDebugWindow>();
    WindowManager->RegisterWindow<CConsoleWindow>();
    WindowManager->RegisterWindow<CInspectorWindow>();
    WindowManager->RegisterWindow<CHierarchyWindow>();
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