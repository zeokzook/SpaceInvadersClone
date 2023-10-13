#include "Sprite.h"
#include <string>

void Sprite::LoadTexture(const char* path)
{
    Vector2 texSize;
    texture = Renderer::GetInstance()->GetTextureFromPath(path, texSize);

    if(texture != NULL)
    {
        destRect.x = 0;
        destRect.y = 0;
        destRect.w = texSize.x;
        destRect.h = texSize.y;
    }
}

Sprite::Sprite(const char* SpritePath)
{
    name = std::string(SpritePath);
    size_t startPos = name.find("/");
    size_t endPos = name.find(".");
    if(startPos != std::string::npos || endPos != std::string::npos)
    {
        name = name.substr(startPos + 1, endPos - startPos - 1);
    }

    LoadTexture(SpritePath);
}

Sprite::Sprite(std::string spriteName, const char* spritePath)
{
    name = spriteName;
    LoadTexture(spritePath);
}

Sprite::~Sprite()
{
}

void Sprite::Update(float deltaTime)
{
}

void Sprite::Render()
{
    if(bIsVisible)
        SDL_RenderCopyF(Renderer::GetInstance()->GetRenderer(), texture, NULL, &destRect);
}

SDL_FRect Sprite::GetRect()
{
    return destRect;
}

Vector2f Sprite::GetPos()
{
    return Vector2f(destRect.x, destRect.y);
}

void Sprite::SetPos(float x, float y)
{
    destRect.x = x;
    destRect.y = y;
}

void Sprite::SetPos(Vector2f pos)
{
    SetPos(pos.x, pos.y);
}

Vector2f Sprite::GetSize()
{
    return Vector2f(destRect.w, destRect.h);
}

void Sprite::SetVisiblity(bool bEnabled)
{
    bIsVisible = bEnabled;
}

bool Sprite::GetVisiblity()
{
    return bIsVisible;
}

void Sprite::SetCollisionEnabled(bool bEnabled)
{
    bCollisionEnabled = bEnabled;
}

bool Sprite::GetCollisionEnabled()
{
    return bCollisionEnabled;
}

void Sprite::MarkDelete()
{
    bCollisionEnabled = false;
    bMarkAsDeleted = true;
}

bool Sprite::GetMarkDelete()
{
    return bMarkAsDeleted;
}

std::string Sprite::GetName()
{
    return name;
}

Vector2f Sprite::GetCenter()
{
    float x = destRect.x + destRect.w * 0.5f;
    float y = destRect.y + destRect.h * 0.5f;
    return Vector2f(x, y);
}

void Sprite::Hit(const std::shared_ptr<Sprite>& otherSprite) 
{
    //printf("Hit! \n");
}
