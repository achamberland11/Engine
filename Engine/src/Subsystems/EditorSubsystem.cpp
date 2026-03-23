#include "EditorSubsystem.h"


void CEditorSubsystem::Start()
{
    WindowManager = new CWindowManager();
    WindowManager->RegisterWindow<CDebugWindow>();
    WindowManager->RegisterWindow<CHierarchyWindow>();
    WindowManager->RegisterWindow<CInspectorWindow>();
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
