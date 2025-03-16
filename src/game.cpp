#include "game.h"
#include "entities.h"
#include <SDL3/SDL.h>

Paddle*         m_P1;
KeyboardInput   m_InputP1;

Paddle*         m_P2;
KeyboardInput   m_InputP2;

Ball*           m_Ball;
Vector2         m_ScreenDimensions;

/*---------------------------------------- */
/*--------- Function Prototypes ---------- */
/*---------------------------------------- */

void MovePaddle             (Paddle* paddle, const KeyboardInput& KeyboardInput, const float deltaTime);
void HandlePaddlePosition   (Paddle* paddle, const Vector2& levelSize);
void MoveBall               (Ball* ball, const float deltaTime);
void HandleBallCollision    (Ball* ball, const Vector2& levelSize);
void ResetBall              (Ball* ball);

/*------------------------------------------*/
/*--------- Function Declarations ----------*/
/*------------------------------------------*/
void GameStart(int screenWidth, int screenHeight)
{
    Vector2 dimensions = {static_cast<float>(screenWidth), static_cast<float>(screenHeight)};
    m_ScreenDimensions = {dimensions};

    m_P1 = AllocPaddle(0, m_ScreenDimensions.y / 2);
    m_P2 = AllocPaddle(m_ScreenDimensions.x - 50, m_ScreenDimensions.y / 2);
    m_Ball = AllocBall(m_ScreenDimensions.x/2, m_ScreenDimensions.y/2);
}

int ProcessInput(SDL_Event* event)
{
    
    if (event->type == SDL_EVENT_QUIT) 
    {
        return SDL_APP_SUCCESS;  
    }
    
    if(event->type == SDL_EVENT_KEY_DOWN)
    {
        if(event->key.key == SDLK_ESCAPE) return SDL_APP_SUCCESS;
    
        if(event->key.key == SDLK_W) m_InputP1.up = true;
        if(event->key.key == SDLK_S) m_InputP1.down = true;

        if(event->key.key == SDLK_UP) m_InputP2.up = true;
        if(event->key.key == SDLK_DOWN) m_InputP2.down = true;
    } 

    if(event->type == SDL_EVENT_KEY_UP)
    {
        if(event->key.key == SDLK_W) m_InputP1.up = false;
        if(event->key.key == SDLK_S) m_InputP1.down = false;

        if(event->key.key == SDLK_UP) m_InputP2.up = false;
        if(event->key.key == SDLK_DOWN) m_InputP2.down = false;
    } 


    return SDL_APP_CONTINUE;
}

void UpdateGame(float deltaTime)
{
   MovePaddle(m_P1, m_InputP1, deltaTime);
   HandlePaddlePosition(m_P1, m_ScreenDimensions);
   
   MovePaddle(m_P2, m_InputP2, deltaTime);
   HandlePaddlePosition(m_P2, m_ScreenDimensions);

   MoveBall(m_Ball, deltaTime);
   HandleBallCollision(m_Ball, m_ScreenDimensions);
}

void MovePaddle(Paddle* paddle, const KeyboardInput& KeyboardInput, const float deltaTime)
{
    paddle->direction = 0;

    if(KeyboardInput.up)   paddle->direction = -1;
    if(KeyboardInput.down) paddle->direction = 1;

    paddle->pos.y += paddle->direction * paddle->speed * deltaTime;
}

void HandlePaddlePosition(Paddle* paddle, const Vector2& levelSize)
{
    if(paddle->pos.y < 0)
        paddle->pos.y = 0;
    if(paddle->pos.y + paddle->h > levelSize.y)
        paddle->pos.y = levelSize.y - paddle->h;
}

void ResetBall(Ball* ball, const Vector2& dir)
{
    ball->pos = {m_ScreenDimensions.x/2, m_ScreenDimensions.y/2};
    ball->dir = dir;
}

void MoveBall(Ball* ball,  const float deltaTime)
{
    ball->pos = ball->pos + (ball->dir * ball->speed * deltaTime);
}

void HandleBallCollision(Ball* ball, const Vector2& levelSize)
{
    //Check for collision with the goal
    if(ball->pos.x < m_P1->pos.x)
    {
        const Vector2 spawnPosition = {1, -1};
        ResetBall(ball, spawnPosition);
        return;
    }
        
    if(ball->pos.x > m_P2->pos.x + m_P2->collider.size.x)
    {
        const Vector2 spawnPosition = {-1, 1};
        ResetBall(ball, spawnPosition);
        return;
    }
        
    //Check for collision with the horizontal walls
    if(ball->pos.y > levelSize.y) 
    {
        ball->pos.y = levelSize.y;
        ball->dir.y = -1.0f;
    }

    if(ball->pos.y < 0)
    {
        ball->pos.y = 0;
        ball->dir.y = 1.0f;
    }


    //Check for collision with the paddles
    if(IsOverlappingBox(m_P1->collider, m_Ball->collider))
    {
        ball->pos.x = m_P1->collider.pivot->x + m_P1->collider.size.x;
        ball->dir.x = 1;
    }

    if(IsOverlappingBox(m_P2->collider, m_Ball->collider))
    {
        ball->pos.x = m_P2->collider.pivot->x - m_Ball->collider.size.x;
        ball->dir.x = -1;
    }
}

void RenderGame(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    const SDL_FRect p1Rect 
    { 
        m_P1->pos.x, 
        m_P1->pos.y, 
        static_cast<float>(m_P1->w), 
        static_cast<float>(m_P1->h)
    };

    const SDL_FRect p2Rect 
    { 
        m_P2->pos.x, 
        m_P2->pos.y, 
        static_cast<float>(m_P2->w), 
        static_cast<float>(m_P2->h)
    };

    const SDL_FRect ballRect
    {
        m_Ball->pos.x,
        m_Ball->pos.y,
        static_cast<float>(m_Ball->size),
        static_cast<float>(m_Ball->size)
    };

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &p1Rect);
    SDL_RenderFillRect(renderer, &p2Rect);
    SDL_RenderFillRect(renderer, &ballRect);


    SDL_RenderPresent(renderer);
}