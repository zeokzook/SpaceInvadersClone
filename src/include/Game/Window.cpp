#include "Window.h"

Window* Window::window = NULL;

Window::~Window()
{
    std::cout << "Cleared Window" << std::endl;
}

Window *Window::GetInstance()
{
    if(window == NULL)
    {
        window = new Window();
    }

    return window;
}