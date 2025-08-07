#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#define WIDTH 900
#define HEIGHT 600
#define COLOUR_WHITE 0xffffffff
#define COLOUR_BLACK 0x00000000

struct Circle
{
    double x;
    double y;
    double r;
};

void FillCircle(SDL_Surface *surface, struct Circle circle, Uint32 color)
{
    double radius_squared = pow(circle.r, 2);
    for (double x = circle.x - circle.r; x <= circle.x + circle.r; x++)
    {
        for (double y = circle.y - circle.r; y <= circle.y + circle.r; y++)
        {
            double distace_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if (distace_squared < radius_squared)
            {
                SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}


int main(int argc, char *argv[])
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Rect pl1 = (SDL_Rect){10, 40, 30, 300};
    SDL_Rect pl2 = (SDL_Rect){700, 200, 30, 300};
    // SDL_Rect ball = (SDL_Rect){400, 200, 30, 30};
    struct Circle ball = {400, 200, 10, 10};
    SDL_Rect ERASE_RECT = {0, 0, WIDTH, HEIGHT};
    SDL_FillRect(surface, &pl2, COLOUR_WHITE);

    int vx = 10;
    int vy = 5;

    int game_running = 1;
    SDL_Event event;
    while (game_running)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            game_running = 0;
        }
        // if (event.type == event.key.type && event.key.state==SDL_PRESSED && event.key.keysym.scancode == SDL_SCANCODE_DOWN )
        // {
        //     pl2.y = pl2.y + 5;
        //     printf("DownKey\n");
        // }
        // if (event.type == event.key.type && event.key.state==SDL_PRESSED && event.key.keysym.scancode == SDL_SCANCODE_UP )
        // {
        //     pl2.y = pl2.y - 5;
        //     printf("UpKey\n");
        // }
        // if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
        // {
        //     pl1.y = event.motion.y;
            
        // }

        // if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
        // {
        //     ball.y = event.motion.y;
        //     ball.x = event.motion.x;
            
        // }

        
        SDL_FillRect(surface, &ERASE_RECT, COLOUR_BLACK);
        // SDL_FillRect(surface, &pl1, COLOUR_WHITE);
        // SDL_FillRect(surface, &pl2, COLOUR_WHITE);
        // SDL_FillRect(surface, &ball, COLOUR_WHITE);
        FillCircle(surface, ball, COLOUR_WHITE);

        ball.x += vx;
        ball.y += vy;
        if (ball.x<0 || ball.x>WIDTH)
        {
            vx=-vx;
        }
        if (ball.y<0 || ball.y>HEIGHT)
        {
            vy=-vy;
        }
        
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

    return 0;
}