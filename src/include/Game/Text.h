#ifndef __TEXT_H__
#define __TEXT_H__

#include <string>
#include "Vector.h"
#include "Renderer.h"
#include <SDL2/SDL_ttf.h>

class Text
{
private:
    TTF_Font* font = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_FRect destRect;

public:
    Text(std::string text, std::string fontName, Vector2f pos, SDL_Color color, int size = 12);
    ~Text();

    void ChangeText(std::string newText);

    void Render();

private:
    void CreateTexture(std::string text, std::string fontName, Vector2f pos, SDL_Color color, int size);
    bool CreateFont(std::string fontName, int size);
};

#endif // __TEXT_H__