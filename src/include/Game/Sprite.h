#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Renderer.h"
#include "Window.h"
#include "HelperFunctions.h"
#include <iostream>
#include <memory>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>

class Sprite
{

protected:
    std::string name;

    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_FRect destRect;

    bool bCollisionEnabled = true;

    bool bIsVisible = true;

    bool bMarkAsDeleted = false;

private:
    void LoadTexture(const char* path);

public:
    Sprite(const char* spritePath);
    Sprite(std::string spriteName, const char* spritePath);
    ~Sprite();

    virtual void Update(float deltaTime);
    void Render();

    SDL_FRect GetRect();

    Vector2f GetPos();
    void SetPos(float x, float y);
    void SetPos(Vector2f pos);

    Vector2f GetSize();

    void SetVisiblity(bool bEnabled);
    bool GetVisiblity();

    void SetCollisionEnabled(bool bEnabled);
    bool GetCollisionEnabled();

    std::string GetName();

    Vector2f GetCenter();

    virtual void MarkDelete();
    bool GetMarkDelete();

    virtual void Hit(const std::shared_ptr<Sprite>& otherSprite);
};

#endif // __SPRITE_H__