#include "RendererSubsystem.h"
#include "SDL3/SDL_log.h"

void CRendererSubsystem::Start()
{
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
    }
}

void CRendererSubsystem::Shutdown()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void CRendererSubsystem::Update(float deltaSeconds)
{
    if (!renderer) return;

    const char* message = "Hello World!";
    const char* frameTimeMessage = FrameText.c_str();
    const char* fpsMessage = fpsText.c_str();
    
    int w = 0, h = 0;
    const float scale = 4.0f;

    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    
    float x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    float y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

    float xFrameTime = 20;
    float yFrameTime = 20;

    float xFPS = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(fpsMessage)) - xFrameTime;
    float yFPS = yFrameTime;

    SDL_SetRenderDrawColor(renderer, ClearColor.r, ClearColor.g, ClearColor.b, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);
    SDL_RenderDebugText(renderer, xFrameTime, yFrameTime, frameTimeMessage);
    SDL_RenderDebugText(renderer, xFPS, yFPS, fpsMessage);
    SDL_RenderPresent(renderer);
}
