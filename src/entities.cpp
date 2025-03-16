#include "entities.h"

Paddle* AllocPaddle(int x, int y)
{
    Vector2   pos = {static_cast<float>(x), static_cast<float>(y)};
    Paddle*   paddle = new Paddle {pos};
   
    paddle->w = 50;
    paddle->h = 300;
    paddle->speed = 1000;
    paddle->direction = 0;

    Vector2 size {static_cast<float>(paddle->w), static_cast<float>(paddle->h)};
    paddle->collider = {&paddle->pos, (size)};
    
    return paddle;
}

void DeallocPaddle(Paddle* paddle)
{
    delete paddle;
}

Ball* AllocBall(int x, int y)
{
    Vector2   pos = {static_cast<float>(x), static_cast<float>(y)};
    Ball*     ball = new Ball{pos};
    
    ball->dir = {1, 1};
    ball->speed = 1000;
    ball->size = 25;

    Vector2 size {static_cast<float>(ball->size), static_cast<float>(ball->size)};
    ball->collider = {&ball->pos, (size)};

    return ball;
};

void DeallocBall(Ball* ball)
{
    delete ball;
}