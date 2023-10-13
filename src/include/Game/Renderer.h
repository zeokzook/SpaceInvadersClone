#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Vector.h"
#include <iostream>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct TexData
{
    TexData(){}
    TexData(SDL_Texture* texture, Vector2 size)
    {
        this->texture = texture;
        this->textureSize = size;
    }

    SDL_Texture* texture = NULL;
    Vector2 textureSize = Vector2(0,0);
};

/**
 *  @todo : Rework get texture from path and keep a reference to surfaces instead
 *          and it returns a weak pointer to a created texture object.
 *          Map of Surfaces that can be used to create textures from the surfaces
 *          instead of storing textures in the map.
 *          Store an array of shared pointers of textures on the renderer
 *          and destroy all of them on Destroy().
*/

class Renderer
{
protected:
    Renderer()
    {
    }

    static Renderer* renderer;
    SDL_Renderer* SDLRenderer = NULL;

    std::map<const char*, TexData> PathToTexDataMap;

public:
    ~Renderer();

    SDL_Renderer* CreateRenderer(SDL_Window* window)
    {
        if(SDLRenderer != NULL)
        {
            printf("Renderer already exists! Returning created renderer.");
            return SDLRenderer;
        }

        SDLRenderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
        return SDLRenderer;
    }

    void Destroy()
    {
        for(auto pair : PathToTexDataMap)
        {
            SDL_DestroyTexture(pair.second.texture);
        }
        PathToTexDataMap.clear();

        if(SDLRenderer != NULL)
        {
            SDL_DestroyRenderer(SDLRenderer);
            SDLRenderer = nullptr;
        }

        delete(renderer);
    }

    SDL_Renderer* GetRenderer()
    {
        if(!SDLRenderer)
        {
            std::cout << "Renderer not created! Please call CreateRenderer()" << std::endl;
            return NULL;
        }

        return SDLRenderer;
    }

    SDL_Texture* GetTextureFromPath(const char* path, Vector2& Size)
    {
        auto pair = PathToTexDataMap.find(path);
        if(pair != PathToTexDataMap.end())
        {
            Size = pair->second.textureSize;
            return pair->second.texture;
        }

        SDL_Surface* tmpSurface = IMG_Load(path);

        if(tmpSurface == NULL)
        {
            printf("Failed to Create Surface: %s\n", SDL_GetError());
            return NULL;
        }

        Size = Vector2(tmpSurface->w, tmpSurface->h);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(SDLRenderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);

        if(tex == NULL)
        {
            printf("Failed to Create Texture: %s\n", SDL_GetError());
            return NULL;
        }

        PathToTexDataMap[path] = TexData(tex, Size);

        return tex;
    }

    Vector2 GetSizeFromTexture(const char* path)
    {
        auto pair = PathToTexDataMap.find(path);
        if(pair != PathToTexDataMap.end())
        {
            return pair->second.textureSize;
        }
        
        Vector2 size;
        GetTextureFromPath(path, size);
        return size;
    }

    static Renderer* GetInstance();
};

#endif // __RENDERER_H__