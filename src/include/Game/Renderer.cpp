#include "Renderer.h"

Renderer* Renderer::renderer = NULL;

Renderer::~Renderer()
{
    std::cout << "Cleared Renderer" << std::endl;
}

Renderer *Renderer::GetInstance()
{
    if(renderer == NULL)
    {
        renderer = new Renderer();
    }

    return renderer;
}