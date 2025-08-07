#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#define WIDTH 1200
#define HEIGHT 800
#define COLOUR_WHITE 0xffffffff
#define COLOUR_BLACK 0x00000000
#define COLOUR_GRAY 0x575353
#define COLOUR_GRASS 0x139119
#define COLOUR_RED 0xFF0000
#define COLOUR_BLUE 0x1000F7
#define COLOUR_ORANGE 0xF76F00

struct Circle
{
    double x;
    double y;
    double r;
};

int IIR(SDL_Rect rect, struct Circle circle)
{
    if (circle.x <= rect.x + rect.w && circle.x > rect.x && circle.y <= rect.y + rect.h && circle.y > rect.y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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

void FillNet(SDL_Surface *surface)
{
    for (int i = 0; i < HEIGHT; i = i + 10)
    {
        SDL_Rect rect = {WIDTH / 2, i, 3, 6};
        SDL_FillRect(surface, &rect, COLOUR_GRAY);
    }
}

int main(int argc, char *argv[])
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    SDL_Rect pl1 = (SDL_Rect){150, 40, 20, 200};
    SDL_Rect pl2 = (SDL_Rect){1050, 200, 20, 100};
    SDL_Rect grass = (SDL_Rect){0, 0, WIDTH, HEIGHT};
    // SDL_Rect ball = (SDL_Rect){400, 200, 30, 30};
    struct Circle ball = {400, 200, 10};
    SDL_Rect ERASE_RECT = {0, 0, WIDTH, HEIGHT};
    SDL_FillRect(surface, &pl2, COLOUR_WHITE);

    int vx = 5;
    int vy = 2;

    int game_running = 1;
    int window_open = 1;
    SDL_Event event;
    SDL_Event event_game;
    while (window_open)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            window_open = 0;
        }

        if (event.type == event.key.type && event.key.state == SDL_PRESSED && event.key.keysym.scancode == SDL_SCANCODE_R)
        {
            game_running = 1;
            printf("R \n");
        }

        int point = 0;
        while (game_running)
        {
            SDL_PollEvent(&event_game);
            ball.x += vx;
            ball.y += vy;
            pl2.y = ball.y - pl2.h / 2;
            // pl1.y = ball.y - pl1.h / 2;

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
            if (event_game.type == SDL_MOUSEMOTION && event_game.motion.state != 0)
            {
                pl1.y = event_game.motion.y-pl1.h/2;
            }

            // if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            // {
            //     ball.y = event.motion.y;
            //     ball.x = event.motion.x;

            // }

            // SDL_FillRect(surface, &ERASE_RECT, COLOUR_BLACK);
            SDL_FillRect(surface, &grass, COLOUR_GRASS);
            SDL_FillRect(surface, &pl1, COLOUR_BLUE);
            SDL_FillRect(surface, &pl2, COLOUR_RED);
            // SDL_FillRect(surface, &ball, COLOUR_WHITE);
            FillCircle(surface, ball, COLOUR_WHITE);
            FillNet(surface);

            if (IIR(pl2, ball))
            {
                vx = -vx;
            }
            if (IIR(pl1, ball))
            {
                vx = -vx;
                point++;
                printf("Points:%d\n",point);
            }

            if (ball.x < 0)
            {
                printf("Game Over\nTry Again\nPress R to Restart\n");
                game_running = 0;
                ball.x = 600;
                ball.y = 400;
            }
            if (ball.y < 0 || ball.y > HEIGHT)
            {
                vy = -vy;
            }

            SDL_UpdateWindowSurface(window);
            SDL_Delay(5);
        }
    }
    return 0;
}