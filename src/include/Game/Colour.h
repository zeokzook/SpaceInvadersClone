#ifndef __LCOLOR_H__
#define __LCOLOR_H__

#include <SDL2/SDL.h>

class Colour
{
public:
    SDL_Color RED()
    {
        SDL_Color col;
        col.r = 255;
        col.g = 0;
        col.b = 0;
        col.a = 255;
        return col;
    };

    SDL_Color GREEN()
    {
        SDL_Color col;
        col.r = 0;
        col.g = 255;
        col.b = 0;
        col.a = 255;
        return col;
    };

    SDL_Color BLUE()
    {
        SDL_Color col;
        col.r = 0;
        col.g = 0;
        col.b = 255;
        col.a = 255;
        return col;
    };

    SDL_Color YELLOW()
    {
        SDL_Color col;
        col.r = 0;
        col.g = 255;
        col.b = 255;
        col.a = 255;
        return col;
    };

    SDL_Color WHITE()
    {
        SDL_Color col;
        col.r = 255;
        col.g = 255;
        col.b = 255;
        col.a = 255;
        return col;
    };

    SDL_Color BLACK()
    {
        SDL_Color col;
        col.r = 0;
        col.g = 0;
        col.b = 0;
        col.a = 255;
        return col;
    };
};

#endif // __LCOLOR_H__