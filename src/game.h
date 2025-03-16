#pragma once

#include <SDL3/SDL.h>

struct KeyboardInput
{
    bool    up;
    bool    down;
};

void GameStart(int screenWidth, int screenHeight);
int  ProcessInput(SDL_Event* event);
void UpdateGame(float deltaTime);
void RenderGame(SDL_Renderer* renderer);