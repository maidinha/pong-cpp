#pragma once

#include "math.h"

/*----------------------------------------*/
/*--------------- Paddle -----------------*/
/*----------------------------------------*/

struct Paddle
{
    Vector2     pos;
    int         w;
    int         h;
    int         speed;
    int         direction;
    BoxCollider collider;
};

Paddle* AllocPaddle(int x, int y);
void    DeallocPaddle(Paddle* paddle);


/*----------------------------------------*/
/*----------------- Ball -----------------*/
/*----------------------------------------*/

struct Ball 
{
    Vector2     pos;
    Vector2     dir;
    int         speed;
    int         size;
    BoxCollider collider;
};

Ball*   AllocBall(int screenWidth, int screenHeight);
void    DeallocBall(Ball* ball);


