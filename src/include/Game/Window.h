#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include "Vector.h"
#include <SDL2/SDL.h>

class Window
{
    Window()
    {
    }

    static Window* window;
    SDL_Window* SDLWindow = NULL;

protected:
    Vector2 windowSize = Vector2(0,0);
    SDL_Rect windowRect;

public:
    ~Window();

    SDL_Window* CreateWindow(const char* windowName, int x, int y, int w, int h)
    {
        if(SDLWindow != NULL)
        {
            printf("Window already exists! Returning created window.");
            return SDLWindow;
        }

        SDLWindow = SDL_CreateWindow(windowName, x, y, w, h, 0);
        windowSize = Vector2(w,h);
        windowRect.x = 0;
        windowRect.y = 0;
        windowRect.w = w;
        windowRect.h = h;
        return SDLWindow;
    }

    void Destroy()
    {
        if(SDLWindow != NULL)
        {
            SDL_DestroyWindow(SDLWindow);
            SDLWindow = nullptr;
        }

        delete(window);
    }

    SDL_Window* GetWindow()
    {
        if(!SDLWindow)
        {
            std::cout << "Window not created! Please call CreateWindow()" << std::endl;
            return NULL;
        }

        return SDLWindow;
    }

    Vector2 GetWindowSize()
    {
        return windowSize;
    }

    SDL_Rect GetWindowRect()
    {
        return windowRect;
    }

    static Window* GetInstance();
};

#endif // __WINDOW_H__