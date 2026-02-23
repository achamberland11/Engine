#include <SDL3/SDL.h>
#include "src/Core/GameEngine.h"

void Start()
{
    CGameEngine::Instance().Init();
}

void Loop()
{
    while (!CGameEngine::Instance().ShouldQuit())
    {
        CGameEngine::Instance().Loop();
    }

    CGameEngine::Instance().Shutdown();
}

int main(int argc, char *argv[])
{
    Start();
    Loop();

    return 0;
}