/*
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
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