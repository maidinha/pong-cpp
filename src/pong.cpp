#define SDL_MAIN_USE_CALLBACKS 1 
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

Uint64 lastFrameTick = 0;
float  deltaTime = 0;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    int screenHeight = 0;
    int screenWidth  = 0;

    if(!SDL_GetWindowSizeInPixels(window, &screenWidth, &screenHeight))
        return SDL_APP_FAILURE;
 
    GameStart(screenWidth, screenHeight);
    
    lastFrameTick = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return static_cast<SDL_AppResult>(ProcessInput(event));
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    deltaTime = static_cast<float>((SDL_GetTicks() - lastFrameTick)) / 1000.0f; 
    lastFrameTick = SDL_GetTicks();

    //In case we need to debug or have longer frames for some reason
    if(deltaTime > 0.5F)
        deltaTime = 0.5F;


    UpdateGame(deltaTime);

    RenderGame(renderer);
    
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}