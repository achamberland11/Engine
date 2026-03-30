#include "EditorSubsystem.h"

#include "InputSubsystem.h"
#include "../Core/GameEngine.h"
#include "../Windows/ToolbarWindow.h"

void CEditorSubsystem::Start()
{
    WorkerThread = new PrimeWorker();

    WindowManager = new CWindowManager();
    WindowManager->RegisterWindow<EToolbarWindow>();
    WindowManager->RegisterWindow<EWorkspaceWindow>();
    WindowManager->RegisterWindow<EDebugWindow>();
    WindowManager->GetWindow<EDebugWindow>()->SetPrimeWorker(WorkerThread);
    WindowManager->GetWindow<EDebugWindow>()->SetDisplayedPrimes(&DisplayedPrimes);
    WindowManager->RegisterWindow<EConsoleWindow>();
    WindowManager->RegisterWindow<EInspectorWindow>();
    WindowManager->RegisterWindow<EHierarchyWindow>();

    EditorMode = new EEditorMode();
    *EditorMode = Editor;
    LastEditorMode = Editor;
}

void CEditorSubsystem::Shutdown()
{
    // Threading
    if (WorkerThread)
    {
        WorkerThread->StopWorker();
        delete WorkerThread;
        WorkerThread = nullptr;
    }
    //
    
    delete WindowManager;
    delete EditorMode;
}

void CEditorSubsystem::Update(float deltaSeconds)
{
    if (*EditorMode != Editor)
        return;

    PollTimer += deltaSeconds;
    if (PollTimer >= 2.0f && WorkerThread)
    {
        PollTimer = 0.0f;
        std::vector<int> newPrimes = WorkerThread->PollPrimes();
        DisplayedPrimes.insert(DisplayedPrimes.end(), newPrimes.begin(), newPrimes.end());
    }

    for (GEntity* entity : CGameEngine::Instance().GetEntities())
    {
        std::vector<GComponent*> components = entity->GetComponents();
        for (GComponent* component : components)
        {
            if (component->GetClass()->bUpdateInEditor)
                component->Update(deltaSeconds);
        }
    }
}

void CEditorSubsystem::Render() const
{
    WindowManager->RenderWindows();
}

void CEditorSubsystem::EnterPlayMode()
{
    SetEditorMode(Play);
    // TODO save entities state to cache

    if (LastEditorMode == Pause) return;
    
    std::vector<GEntity*> entities = CGameEngine::Instance().GetEntities();
    for (GEntity* entity : entities)
    {
        entity->Start();
    }
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
