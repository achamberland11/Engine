#include "EditorSubsystem.h"

#include "InputSubsystem.h"
#include "../Core/GameEngine.h"

void CEditorSubsystem::Start()
{
    WindowManager = new CWindowManager();
    WindowManager->RegisterWindow<EWorkspaceWindow>();
    WindowManager->RegisterWindow<EDebugWindow>();
    WindowManager->RegisterWindow<EConsoleWindow>();
    WindowManager->RegisterWindow<EInspectorWindow>();
    WindowManager->RegisterWindow<EHierarchyWindow>();

    EditorMode = new EEditorMode();
    *EditorMode = Editor;
}

void CEditorSubsystem::Shutdown()
{
    delete WindowManager;
    delete EditorMode;
}

void CEditorSubsystem::Update(float deltaSeconds)
{
    if (*EditorMode != Editor)
        return;

    /*for (GEntity* entity : CGameEngine::Instance().GetEntities())
    {
        if (entity->GetClass()->bUpdateInEditor)
            entity->Update(deltaSeconds);
    }*/

}

void CEditorSubsystem::Render() const
{
    WindowManager->RenderWindows();
}

void CEditorSubsystem::EnterPlayMode()
{
    SetEditorMode(Play);
    // TODO save entities state to cache
}

void CEditorSubsystem::EnterPauseMode()
{
    SetEditorMode(Pause);
}

void CEditorSubsystem::ExitPlayMode()
{
    SetEditorMode(Editor);
    // TODO load cached entities state
}
