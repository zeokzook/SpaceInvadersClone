#include "Text.h"

Text::Text(std::string text, std::string fontName, Vector2f pos, SDL_Color color, int size)
{
    CreateTexture(text, fontName, pos, color, size);
}

Text::~Text()
{
    if(textTexture)
    {
        SDL_DestroyTexture(textTexture);
    }
    
    if(font)
    {
        TTF_CloseFont(font);
    }
}

void Text::ChangeText(std::string newText)
{
    SDL_DestroyTexture(textTexture);

}

void Text::Render()
{
    SDL_RenderCopyF(Renderer::GetInstance()->GetRenderer(), textTexture, NULL, &destRect);
}

void Text::CreateTexture(std::string text, std::string fontName, Vector2f pos, SDL_Color color, int size)
{
    if(!CreateFont(fontName, size))
    {
        printf("Text: Failed to create font: %s\n", TTF_GetError());
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    if(!surface)
    {
        printf("Text: Failed to create surface: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), surface);

    if(!texture)
    {
        printf("Text: Failed to create Texture: %s\n", TTF_GetError());
        return;
    }

    destRect.h = surface->h;
    destRect.w = surface->w;
    destRect.x = pos.x;
    destRect.y = pos.y;

    textTexture = texture;

    SDL_FreeSurface(surface);

}

bool Text::CreateFont(std::string fontName,  int size)
{
    if(font)
    {
        TTF_CloseFont(font);
    }

    std::string path = "./assets/fonts/" + fontName;

    font = TTF_OpenFont(path.c_str(), size);

    return font;
}
