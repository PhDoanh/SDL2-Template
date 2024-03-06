#include <../inc/SDL.h>
#include <../inc/SDL_image.h>
#include <../inc/SDL_mixer.h>
#include <../inc/SDL_net.h>
#include <../inc/SDL_ttf.h>
#include <../inc/SDL_render.h>
#include <../inc/SDL_surface.h>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Error: SDL failed to initialize\nSDL Error: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        std::cout << "Error: Failed to open window\nSDL Error: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Surface *logoSurface = IMG_Load("res/logo.png");
    if (!logoSurface)
    {
        std::cout << "Error: Failed to load image\nSDL_Image Error: " << IMG_GetError() << '\n';
        return 1;
    }

    SDL_Texture *logo = SDL_CreateTextureFromSurface(renderer, logoSurface);
    if (!logo)
    {
        std::cout << "Error: Failed to create texture\n";
        return 1;
    }

    SDL_Rect logoDst = {
        .x = (SCREEN_WIDTH / 2) - 200,  // logo with 400 / 2
        .y = (SCREEN_HEIGHT / 2) - 200, // logo height 400 / 2
        .w = 400,                       // logo width
        .h = 400                        // logo height
    };

    SDL_FreeSurface(logoSurface);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x0c, 0x1c, 0x2c, 0x00);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, logo, NULL, &logoDst);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(logo);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();

    return 0;
}